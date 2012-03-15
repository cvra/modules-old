//      cvra_adc.h
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


#ifndef _CVRA_ADC_H_
#define _CVRA_ADC_H_

#include <aversive.h>

/** @struct cvra_adc_t
 *  @brief Une instance du driver Analog In. 
 * 
 * Ce driver se charge de lire les valeurs d'un ADC108S102 qui est un 
 * ADC 8 voies connecte en SPI. */
typedef struct {
    uint32_t *spi_adress;	///< L'adresse du module SPI.
    uint8_t next_read;		///< Le prochain channel a etre lu.
    int16_t values[8];		///< Les valeurs des 8 canaux.
} cvra_adc_t;

/** Inits the CVRA analog in module. */
void cvra_adc_init(cvra_adc_t *adc, void *adress, int irq_number);

/** Returns the selected ADC channel's value. */
int16_t cvra_adc_get_value(cvra_adc_t *adc, int input);

/** Starts the scan of the 8 input lines. */
void cvra_adc_start_scan(cvra_adc_t *adc);

#endif
