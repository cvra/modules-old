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

void cvra_beacon_init(cvra_beacon_t *beacon, void *adress, int irq_number, int pwm, float gain, float offset)
{
    int ret;
    alt_u8 i;
    
    
    beacon->beacon_adress = adress;
    beacon->nb_beacon = 0;
    beacon->period = 0;
    beacon->gain = gain;
    beacon->offset = offset;
    
    for (i=0;i<NB_BEACON_MAX;i++) {
      beacon->beacon[i].direction = 0;
      beacon->beacon[i].distance = 0;
    }
    
    // Empty the data fifo
    while (IORD(beacon->beacon_adress, STATUS_REGISTER) ^ FIFO_EMPTY) {
      IORD(beacon->beacon_adress, DATA_REGISTER);
    }
    
    /* Start motor with 50% PWM = 127*/
    IOWR(beacon->beacon_adress, PWM_REGISTER, pwm);
    
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

void cvra_beacon_set_direction_offset(cvra_beacon_t *beacon, float value)
{
    beacon->direction_offset = value;
}

/* Interrupt function called one per rotation*/
void cvra_beacon_manage(void *a) {
    alt_u32 actual_index;
    alt_u32 actual_edge;
    alt_u32 start_edge;
    alt_u32 direction;
    alt_u32 distance;
    alt_u32 end_edge;
    alt_u8 i = 0;

    typedef enum {
      first_beacon,
      start_beacon,
      end_beacon
    }search_state;

    search_state state = first_beacon;
    cvra_beacon_t *beacon = (cvra_beacon_t *)a;
    
    /*Clear IRQ flag*/
    IOWR(beacon->beacon_adress, STATUS_REGISTER, 0);

    //Clear old beacon informations
    beacon->nb_beacon = 0;
    for (i=0;i<NB_BEACON_MAX;i++) {
      beacon->beacon[i].direction = 0;
      beacon->beacon[i].distance = 0;
    }

    actual_index = IORD(beacon->beacon_adress, INDEX_REGISTER);
    beacon->period = actual_index - beacon->lastindex;
    beacon->firstedge = IORD(beacon->beacon_adress, FIRST_EDGE_REGISTER);
    while (~IORD(beacon->beacon_adress, STATUS_REGISTER) & FIFO_EMPTY){
      actual_edge = IORD(beacon->beacon_adress, DATA_REGISTER);
      switch (state){
        case first_beacon:
          if (actual_edge == beacon->firstedge){
            start_edge = actual_edge;
            state = end_beacon;
          }
          break;
          
        case start_beacon:
          start_edge = actual_edge;
          state = end_beacon;
          break;
          
        case end_beacon:
          direction = (((alt_u64)actual_edge + (alt_u64)start_edge)>>1)-beacon->lastindex;
          distance = actual_edge - start_edge;
          beacon->beacon[beacon->nb_beacon].direction = (direction*360.0)/beacon->period;
          beacon->beacon[beacon->nb_beacon].distance = ((distance*360.0)/beacon->period) * beacon->gain + beacon->offset;

          beacon->beacon[beacon->nb_beacon].direction += beacon->direction_offset; 

          // Keeps the angle between +180 and -180
          if(beacon->beacon[beacon->nb_beacon].direction > 180)
            beacon->beacon[beacon->nb_beacon].direction -= 360; 
          beacon->nb_beacon++;
          state = start_beacon;
          break;
          
        default:
          break;
      }
    }

    beacon->lastindex = actual_index;
}
