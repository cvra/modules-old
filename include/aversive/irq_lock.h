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
 *  Revision : $Id: irq_lock.h,v 1.1.2.1 2007-05-23 17:18:09 zer0 Exp $
 *
 */

/** \file modules/base/utils/irq_lock_macros.h
 *  \brief Interface of the utils module
 *   
 *   here are defined the three macros : 
 *
 *  IRQ_LOCK(flags);              this saves interrupt state
 *  IRQ_UNLOCK(flags);            this restores interrupt state
 *  
 *  code example follows: 
 *
 *    uint8_t flags;
 *    IRQ_LOCK(flags);
 *      // code to be protected against interrupts ...
 *    IRQ_UNLOCK(flags); // needs to be associated with an unlock
 *  
 */


#ifndef _AVERSIVE_IRQ_LOCK_H_
#define _AVERSIVE_IRQ_LOCK_H_

#ifdef COMPILE_ON_ROBOT
#include <nios2.h>
#define GLOBAL_IRQ_ARE_MASKED() (0)


/** Sauvegarde la valeur de STATUS.PIE dans flags, et desactive STATUS.PIE
 * ensuite. */
#define IRQ_LOCK(flags) do {	                                    \
                            uint32_t t;                             \
                            NIOS2_READ_STATUS(t);                   \
                            flags = (t & NIOS2_STATUS_PIE_MSK);     \
                            t = t & ~(NIOS2_STATUS_PIE_MSK);        \
                        } while(0);
                        
#define IRQ_UNLOCK(flags) do {                                      \
                            uint32_t t;                             \
                            NIOS2_READ_STATUS(t);                   \
                            t |= flags;                             \
                            NIOS2_WRITE_STATUS(t);                  \
                        } while(0);

#else 

#define IRQ_LOCK(flags) flags=0
#define IRQ_UNLOCK(flags) flags=1

#endif /*COMPILE_ON_ROBOT*/

#endif /* _AVERSIVE_IRQ_LOCK_H_ */
