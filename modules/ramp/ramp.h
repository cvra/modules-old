/*  
 *  Copyright Droids Corporation, Microb Technology, Eirbot (2005)
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 */


/** @file ramp.h
 * @brief This modules provides a speed ramp.
 *
 * This modules is used to do a speed regulation on top of a position
 * based system. This functions outputs a position value, moving at the given
 * speed an therefore achieving a speed regulation. This technique is used by
 * the LM629 modules so it should not be too bad.
 *
 * @todo Test this module, should work though.
 */



#ifndef _RAMP_H_
#define _RAMP_H_

/** Instance of the ramp filter. */
struct ramp_filter {
	uint32_t var_neg;   /**< Maximal negative variation. */        
	uint32_t var_pos;   /**< Maximal positive variation. */ 
    int32_t prev_speed; /**< Speed at the previous iteration. */
	int32_t prev_out;   /**< Previous position output. */
};



/** @brief Initialize a ramp instance.
 *
 * This function initializes the ramp filter, setting all values to 0.
 * @param [in,out] r The ramp instance to initialize.
 */
void ramp_init(struct ramp_filter * r );


/** @brief Set acceleration.
 *
 * This function sets the maximal acceleration, both negative and positive.
 * @param [in,out] r The ramp instance.
 * @param [in] neg Maximal deceleration.
 * @param [in] pos Maximal acceleration.
 */
void ramp_set_vars(struct ramp_filter * r, uint32_t neg, uint32_t pos);


/** @brief Applies a filter that limits the acceleration.
 *
 * This function limits the acceleration by comparing the variatinon between the
 * last velocity and the consigned velocity. If the acceleration is to high the 
 * consigned velocity is set to the highest velocity.
 * @param [in] r The ramp instance, cast to void * to be compatible with CSM.
 * @param [in] in A velocity consign.
 * @returns A the filtered velocity consign.
 */
int32_t ramp_do_filter(void * r, int32_t in);

#endif /* ifndef _RAMP_H */
