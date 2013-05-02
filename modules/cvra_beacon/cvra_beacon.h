//      cvra_beacon.h
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


#ifndef _CVRA_BEACON_H_
#define _CVRA_BEACON_H_

//#include <aversive.h>
#include <alt_types.h>

#define NB_BEACON_MAX 8

/** @struct cvra_adc_t
 * @note: instance of the beacon
 */
typedef struct {
  float direction;
  float distance;
} beacon_pos_t;

typedef struct {
    alt_u32 *beacon_adress;	///< adress of the beacon module
    alt_u32 period;	        ///< periode time in
    alt_u32 lastindex;      ///< index of last scan
    alt_u32 firstedge;
    float   gain;
    float   offset;
    alt_u8  nb_beacon;
    beacon_pos_t beacon[NB_BEACON_MAX];
} cvra_beacon_t;

/** Inits the CVRA beacon module. */
void cvra_beacon_init(cvra_beacon_t *beacon, void *adress, int irq_number, int pwm, float gain, float offset);

#endif
