
#ifndef _FAST_MATH_H_
#define _FAST_MATH_H_

/** Initializes the fast math library.
 *
 * This functions precomputes the lookup table used in others fast_* functions.
 * @warning This function must be called before any call to fast_*.
 * @author Mathieu Rouvinez, CVRA
 */
void  fast_math_init();     //################# DO NOT FORGET #################

/** Computes a the absolute value of a float.
 *
 * This function computes the absolute value of a float by masking its MSB
 * (sign in IEEE754 floats).
 * @author Mathieu Rouvinez, CVRA
 */
float fast_fabsf    (float v);

/** Computes a sine.
 *
 * This function computes a sine by using a taylor series expansion.
 */
float fast_sinf     (float v);

/** Computes a cosine.
 *
 * This function computes a cosine by using a taylor series expansion.
 */
float fast_cosf     (float v);

/** Computes an atan2.
 *
 * This function computes an atan2 by using a taylor series expansion.
 */
float fast_atan2f   (float y, float x);

/** Computes a square root
 *
 * This function computes a square root by using a fast lookup table. */
float fast_sqrtf    (float v);

/** Computes the inverse of a square root using Carmack's trick. */
float fast_invsqrtf (float v);

/** Benchmarks the library. */
void fast_benchmark(void);

#endif
