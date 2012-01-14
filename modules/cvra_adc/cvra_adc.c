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
#define RXDATA_REGISTER             0
#define TXDATA_REGISTER             1
#define STATUS_REGISTER             2
#define CONTROL_REGISTER            3
#define RESERVED_REGISTER           4
#define SLAVE_SELECT_MASK_REGISTER  5

void cvra_adc_init(cvra_adc_t *adc, void *adress , int irq_number) {
    int i=8;
    int val;
    adc->spi_adress = adress;
    while(i--) {
        adc->values[i]=0;
    }
    adc->next_read=0;
    
    /* Pas de CS ni d'interrupt. */
    IOWR(adc->spi_adress, CONTROL_REGISTER, 0);
    
    /* Deselect ADC */
    IOWR(adc->spi_adress, SLAVE_SELECT_MASK_REGISTER, 0x01);

#ifdef COMPILE_ON_ROBOT    
    val = alt_ic_isr_register(0, irq_number, cvra_adc_manage, (void *)adc, 0);
    val = alt_ic_irq_enable (0,irq_number);
#endif

}

/* Devrait etre appellee depuis un contexte d'interrupt sur TXRDY. */
void cvra_adc_manage(void *a) {
    cvra_adc_t *adc = (cvra_adc_t *)a;
    adc->values[(adc->next_read+7)&0x07]=(IORD(adc->spi_adress, RXDATA_REGISTER)>>2) & 0x3ff;
    IOWR(adc->spi_adress, STATUS_REGISTER, 0);
    adc->next_read++;
    if (adc->next_read<8){
      IOWR(adc->spi_adress, TXDATA_REGISTER, (adc->next_read)<<11);
    } else {
    	  IOWR(adc->spi_adress, CONTROL_REGISTER, 0);
    }
}
void cvra_adc_start_scan(cvra_adc_t *adc) {
	IOWR(adc->spi_adress, STATUS_REGISTER, 0); //Clear all error flags
	IORD(adc->spi_adress, RXDATA_REGISTER); //Dummy read to clear receive buffer
	adc->next_read = 0;
	IOWR(adc->spi_adress, CONTROL_REGISTER, (1<<10) | (1<<7));
	//Start scan
	IOWR(adc->spi_adress, TXDATA_REGISTER, (adc->next_read)<<11);
}

int16_t cvra_adc_get_value(cvra_adc_t *adc, int input) {
    if(input >= 8 || input < 0)
        return -1;
    return adc->values[input];
}
