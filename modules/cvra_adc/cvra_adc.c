//      cvra_adc.c
//      
//      Copyright 2011 Antoine Albertelli <a.albertelli@cvra.ch>
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

#include "cvra_adc.h"
#include <stdlib.h>
#include <aversive.h>
#include <aversive/error.h>

/* Register map */
#define TXDATA_REGISTER             0
#define RXDATA_REGISTER             1
#define STATUS_REGISTER             2
#define CONTROL_REGISTER            3
#define RESERVED_REGISTER           4
#define SLAVE_SELECT_MASK_REGISTER  5

void cvra_adc_init(cvra_adc_t *adc, void *adress) {
    NOTICE(0, "cvra_adc_init");
    int i=8;
    adc->spi_adress = adress;
    while(i--) {
        adc->values[i]=0;
    }
    adc->next_read=0;
    
    /* Configuration du hardware. */
    
    /* Force le signal CS et interrupt sur RXRDY. */
    IOWR(adc->spi_adress, CONTROL_REGISTER, (1<<10) | (1<<7));
    
    /* On selectionne le CS 1. */
    IOWR(adc->spi_adress, SLAVE_SELECT_MASK_REGISTER, 0x01);
    
    ///TODO: Implementer l'interrupt
}

/* Devrait etre appellee depuis un contexte d'interrupt sur TXRDY. */
void cvra_adc_manage(void *a) {
    cvra_adc_t *adc = (cvra_adc_t *)a;
    adc->values[adc->next_read]=IORD(adc->spi_adress, RXDATA_REGISTER);
    adc->next_read = (adc->next_read+1)%8;
    IOWR(adc->spi_adress, TXDATA_REGISTER, adc->next_read<<3);
}

int cvra_adc_get_value(cvra_adc_t *adc, int input) {
    if(input >= 8 || input < 0)
        return -1;
    return adc->values[input];
}
