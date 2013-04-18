//      cvra_beacon.c
//      
//      Copyright 2013 Rouven Althaus <r.althaus@cvra.ch>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include "cvra_beacon.h"
#include <stdlib.h>
#include <io.h>
#include <sys/alt_irq.h>
//#include <aversive.h>
//#include <aversive/error.h>

#ifndef COMPILE_ON_ROBOT
#include <stdio.h>
#endif

/* Register map */
#define STATUS_REGISTER             0
#define INDEX_REGISTER              1
#define DATA_REGISTER               2
#define PWM_REGISTER                3
#define FIRST_EDGE_REGISTER         4

/* Status regsiter bitmap */
#define FIFO_FULL    0x01
#define FIFO_EMPTY   0x02

void cvra_beacon_manage(void *a);

void cvra_beacon_init(cvra_beacon_t *beacon, void *adress, int irq_number)
{
    int ret;
    
    beacon->beacon_adress = adress;
    beacon->nb_beacon = 0;
    beacon->period = 0;
    
    // Empty the data fifo
    while (IORD(beacon->beacon_adress, STATUS_REGISTER) ^ FIFO_EMPTY) {
      IORD(beacon->beacon_adress, DATA_REGISTER);
    }
    
    /* Start motor with 50% PWM */
    IOWR(beacon->beacon_adress, PWM_REGISTER, 0xff);
    
    /* Store actuel index */
    beacon->lastindex = IORD(beacon->beacon_adress, INDEX_REGISTER);
    
    /*Clear IRQ flag*/
    IOWR(beacon->beacon_adress, STATUS_REGISTER, 0);
    

//#ifdef COMPILE_ON_ROBOT
    ret=alt_ic_isr_register(0, irq_number, cvra_beacon_manage, (void *)beacon, 0);
//    alt_ic_irq_enable (0,irq_number);
//#else
//    printf("registring adc on adress %p using irq %d\n", adress, irq_number);
//#endif

}

/* Devrait etre appellee depuis un contexte d'interrupt sur TXRDY. */
void  cvra_beacon_manage(void *a) {
    alt_u32 actual_index;
    static alt_u32 last_call = 0;
    alt_u8 i = 0;

//    printf("%d\n", (int)(uptime_get() - last_call));
    last_call = uptime_get();
    cvra_beacon_t *beacon = (cvra_beacon_t *)a;
    actual_index = IORD(beacon->beacon_adress, INDEX_REGISTER);
    beacon->period = actual_index - beacon->lastindex;
/*    if(beacon->period != 0)
        printf("period: %d\n", (int)beacon->period);  */

    beacon->lastindex = actual_index;
    beacon->firstedge = IORD(beacon->beacon_adress, FIRST_EDGE_REGISTER);
//    printf("fe : \t%ud\n", (unsigned int)beacon->firstedge);
    while (IORD(beacon->beacon_adress, STATUS_REGISTER) ^ FIFO_EMPTY){
#if 1
        IORD(beacon->beacon_adress, DATA_REGISTER);
#else
        printf("%d : \t%ud\n", i, (unsigned int)IORD(beacon->beacon_adress, DATA_REGISTER));
#endif
        i++;
    }
//    printf("%d", i);
    beacon->nb_edges = i;
    /*Clear IRQ flag*/
    IOWR(beacon->beacon_adress, STATUS_REGISTER, 0);
}
