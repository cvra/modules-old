/*
 *  Copyright Droids Corporation (2007)
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
 *  Revision : $Id: blocking_detection_manager.c,v 1.1.2.7 2009-05-18 12:29:10 zer0 Exp $
 *
 *  Olivier MATZ <zer0@droids-corp.org>
 */

/* blocking detection manager */

#include <stdio.h>
#include <string.h>
#include <aversive/error.h>

#include <blocking_detection_manager.h>




/** init module, give the robot system to use as a parameter */
void bd_init(struct blocking_detection * bd, struct cs *cs)
{
    uint8_t flags;
    IRQ_LOCK(flags);
    memset(bd, 0, sizeof(*bd));
    bd->cs = cs;
    IRQ_UNLOCK(flags);
    
}


/** reset current blocking */
void bd_reset(struct blocking_detection * bd)
{
    uint8_t flags;
    IRQ_LOCK(flags);
    bd->cpt = 0;
    IRQ_UNLOCK(flags);
}

void bd_set_thresholds(struct blocking_detection *bd, uint16_t err_thres, uint16_t cpt_thres) {
    uint8_t flags;
    IRQ_LOCK(flags);
    bd->cpt_thres = cpt_thres;
    bd->err_thres = err_thres;
    IRQ_UNLOCK(flags);
    
}



/** function to be called periodically */
void bd_manage(struct blocking_detection * bd)
{

    if(cs_get_error(bd->cs) > bd->err_thres || cs_get_error(bd->cs) < -(bd->err_thres)) {
        bd->cpt++;
    }
    else
        bd->cpt=0;
}

/** get value of blocking detection */
uint8_t bd_get(struct blocking_detection * bd)
{
    uint8_t ret, flags;
    IRQ_LOCK(flags);
    ret = (bd->cpt_thres && (bd->cpt >= bd->cpt_thres));
    IRQ_UNLOCK(flags);
    return ret;
}
