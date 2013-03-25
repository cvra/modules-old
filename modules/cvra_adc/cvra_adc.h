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
 * @note: instance of the Analog In driver
 *
 * the driver reads values from an ADC108S102 which is a 8 channel ADC 
 * connected in SPI */
typedef struct {
    uint32_t *spi_adress;   ///< adress of the SPI module
    uint8_t next_read;      ///< next channel to be read
    int16_t values[8];      ///< values of the 8 channels
} cvra_adc_t;

/** Inits the CVRA analog in module. */
void cvra_adc_init(cvra_adc_t *adc, void *adress, int irq_number);

/** Returns the selected ADC channel's value. */
int16_t cvra_adc_get_value(cvra_adc_t *adc, int input);

/** Starts the scan of the 8 input lines. */
void cvra_adc_start_scan(cvra_adc_t *adc);

#endif
