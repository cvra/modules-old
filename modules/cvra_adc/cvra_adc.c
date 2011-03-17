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

void send_and_receive(void * adress, char *tx, char *rx) {
    /* Ici il faut ecrire dans le SPI. */
    if(tx!=NULL) {
        IOWR((char *)(adress), 0, *tx);
    }
    if(rx!=NULL) {
        *rx = IORD((char *)(adress), 0);
    }
}

void cvra_adc_init(cvra_adc_t *adc, void *adress) {
    NOTICE(0, "cvra_adc_init");
    int i=8;
    adc->spi_adress = adress;
    while(i--) {
        adc->values[i]=0;
    }
}
void cvra_adc_manage(void *adc) {
    ///FIXME: A remplir une fois que j'ai la datasheet
}

int cvra_adc_get_value(cvra_adc_t *adc, int input) {
    return adc->values[input];
}
