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
 *  Revision : $Id: wait.h,v 1.1.2.1 2007-05-23 17:18:09 zer0 Exp $
 *
 */

/** 
 * This file is an interface for wait functions, in order to put the 
 * microcontroller in a loop state.
 */

/**********************************************************/

#ifndef _AVERSIVE_WAIT_H_
#define _AVERSIVE_WAIT_H_

#include <aversive.h>

#include <unistd.h>

#define wait_3cyc(n) do { volatile int a = 0; a++; } while (0)
#define wait_4cyc(n) do { volatile int a = 0; a++; } while (0)
#define wait_ms(n) do {printf("wait_ms not implemented yet."); } while(0);

#endif /* _AVERSIVE_WAIT_ */
