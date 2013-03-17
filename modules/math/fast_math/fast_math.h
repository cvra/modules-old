
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
 * Validity range: [-pi,pi]
 */
float fast_sinf     (float v);

/** Computes a cosine.
 *
 * This function computes a cosine by using a Taylor series expansion.
 * Validity range: [-pi,pi]
 */
float fast_cosf     (float v);

/** Computes a tangent.
 *
 * This function computes a tangent by using a lookup table.
 */
float fast_tanf     (float v);

/** Computes arcsine.
 *
 * This function computes an arcsine by using a lookup table.
 */
float fast_asinf    (float v);

/** Computes an arccosine.
 *
 * This function computes an arccosine by using a lookup table.
 */
float fast_acosf    (float v);

/** Computes an arctangent.
 *
 * This function computes an arctangent by using a lookup table.
 */
float fast_atanf    (float v);

/** Computes an atan2.
 *
 * This function computes an atan2 by using a Taylor series expansion.
 */
float fast_atan2f   (float y, float x);

/** Computes a square root
 *
 * This function computes a square root by using a fast lookup table (Hsieh).
 */
float fast_sqrtf    (float v);

/** Computes the inverse of a square root using Carmack's trick (Lomont). */
float fast_invsqrtf (float v);

/** Computes the inverse of a float using a very rough approximation. */
float fast_invf     (float v);

/** Benchmarks the library. */
void  fast_benchmark(void);

#endif
