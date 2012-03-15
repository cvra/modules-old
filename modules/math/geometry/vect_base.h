/*
 *  Copyright Droids Corporation (2009)
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
 *  Revision : $Id: f16.h,v 1.6.4.3 2008-05-10 15:06:26 zer0 Exp $
 *
 */

#ifndef _VECT_BASE_H_
#define _VECT_BASE_H_

/** \addtogroup Geometrie
 * @{ */

typedef struct _vect_t {
  float x;
  float y;
} vect_t;

typedef struct _point_t {
  float x;
  float y;
} point_t;

/** Computes dot product between 2 vectors. */
float vect_pscal(vect_t *v, vect_t *w);

/** Returns the Z component of a cross product. */
float vect_pvect(vect_t *v, vect_t *w);

/** Returns the sign of the dot product. */
int8_t vect_pscal_sign(vect_t *v, vect_t *w);

/** Returns the sign of the Z component of the cross product. */
int8_t vect_pvect_sign(vect_t *v, vect_t *w);

/** Computes the norm of a vector. */
float xy_norm(float x1, float y1, float x2, float y2);

/** Computes the norm of a vector. */
float pt_norm(const point_t *p1, const point_t *p2);

/** Computes the norm of a vector. */
float vect_norm(const vect_t *v);

/** Rotates v by 90 deg CCW */
void vect_rot_trigo(vect_t *v);

/** Rotates V by 90 deg CW. */
void vect_rot_retro(vect_t *v);

/** Returns the polar angle of v. */
float vect_get_angle(vect_t *v, vect_t *w);

/** Scales v by a l factor. */
void vect_resize(vect_t *v, float l);
/** @} */
#endif /* _VECT_BASE_H_ */
