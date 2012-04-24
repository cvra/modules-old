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

#ifndef _LINES_H_
#define _LINES_H_

/** \addtogroup Geometrie 
 * @{ */

typedef struct _line {
	float a;
	float b;
	float c;
} line_t;


/** Converts 2 points to a line. */
void pts2line(const point_t *p1, const point_t *p2, line_t *l);

/** Projects a point on a line. */
void proj_pt_line(const point_t *p, const line_t *l, point_t *p_out);

/** Checks if 2 lines are intersecting. 
  * @return 0 if l1 & l2 dont cross, 1 if they cross, 2 if they are the same lines. 
  * @param [out] p The intersection point, only meaningful for result 1. */
uint8_t intersect_line(const line_t *l1, const line_t *l2, point_t *p);

/** Intersects 2 segments.
 * @return 0 dont cross, 1 cross, 2 cross on point, 3 parallel and one point in
 * @param [out] p The crossing point coordinates (dummy for 0 1 or 3
 * result).
 */
uint8_t intersect_segment(const point_t *s1, const point_t *s2,
		  const point_t *t1, const point_t *t2,
		  point_t *p);

/** @brief Translate the line.
 * 
 * Translates the line by a given vector.
 * @param l The line to translate. 
 * @param v The translation vector. */
void line_translate(line_t *l, vect_t *v);

/** @} */
#endif /* _LINES_H_ */
