/* File        : modules/math/fast_math/fast_math.c
 * Author      : Mathieu Rouvinez
 * Project     : CVRA Robot #1, SwissRobot 2012
 * State       : appears to work
 * Creation    : 2012.04.24  (yes, YYYY.MM.DD, because it's logical)
 * Last modif. : 2012.04.28
 * Description : quite fast math function, accurate enough, nothing more
 * Notes       : some code borrowed from other programmers, didn't ask them...
 * Disclaimer  : works on my machine, check if it does on your machine too
 * Copyright   : none in my opinion, tell everyone
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "../../strat.h"

#define F_PI   3.14159265358979323846f
#define F_PI_2 1.57079632679489661923f
#define F_PI_4 0.785398163397448309616f
#define F_1_PI 0.318309886183790671538f
#define F_2_PI 0.636619772367581343076f


// DECLARATIONS

static unsigned int fast_sqrtf_lut[0x10000];    // fast_sqrtf lookup table


// DEFINITIONS

inline float fast_fabsf(float v)
{
    union {float f; unsigned int u;} i = {v};   // union, for aliasing
    i.u &= 0x7FFFFFFFu;                         // bitmask, set MSB to 0
    return i.f;                                 // done, neat !
}

/*
inline float fast_fabsf(float v)    // DOES NOT WORK ON NIOS II
{                                   //  endianness ? alignment ?
    unsigned int* p = (unsigned int*) &v;   // pointer, for aliasing
    *p &= 0x7FFFFFFFu;                      // bitmask, set MSB to 0
    return v;                               // done, neat !
}
*/

float fast_sinf(float v)    // ref: http://dotancohen.com/eng/taylor-sine.php
{
    int q = 0;
    if (v < 0.0f) q = -1;

    int c = v * M_2_PI;     // turns

    q = q + c;

    float s = (float)q * F_PI_2;   // turns shift

    v = v - s;  // our angle now fits in the range [0,PI_2]

    q = q&3;    // quadrant number

    if (q==1 || q==3) v = F_PI_2 - v;   // quad II or IV, complementary angle
    if (q==2 || q==3) v = -v;           // quad III or IV, flip sign of angle

    const float v2 = v*v;
    const float c1 = 0.99989187717437744000f;  //  1.000000f ~= 1/1! = 1/1
    const float c2 =-0.16596019268035889000f;  // -0.166667f ~= 1/3! = 1/6
    const float c3 = 0.00760292448103427890f;  //  0.008333f ~= 1/5! = 1/120

    return v*(c1+v2*(c2+v2*(c3)));  // compute Taylor series terms and return
}


float fast_cosf(float v)
{
    int q = -(int)(v<0.0f);     // get number of shifts from quadrant I
    q = q + (int)(v*F_2_PI);    // get number of shifts from quadrant I
    v = v - (float)(q)*F_PI_2;  // our angle now fits in the range [0,PI_2]

    q = q&3;    // quadrant number = number of quadrant shifts modulo 4

    float s = 1.0f;     // multiplicator, flipping or not the sign of the cos

    if (q==1 || q==3) v = F_PI_2 - v;   // quad II or IV, complementary angle
    if (q==1 || q==2) s = -1.0f;        // quad II or III, flip sign of cos

    const float v2 = v*v;
    const float c1 = 0.99903213977813721000f;  //  1.000000f ~= 1/0! = 1/1
    const float c2 =-0.49264952540397644000f;  // -0.500000f ~= 1/2! = 1/2
    const float c3 = 0.03556701540946960400f;  //  0.041667f ~= 1/4! = 1/24

    return s*(c1+v2*(c2+v2*(c3)));  // compute Taylor series terms and return
}

float fast_atan2f(float y, float x)
{
    const float absy = fabsf(y);
    const float absx = fabsf(x);

    if (absy < 1e-5f)   // if y near 0, angle is 0 or PI, depending on x
    {
        if (x >= 0.0f) return 0.0f;
        else           return F_PI;
    }

    if (absx < 1e-5f)   // if x near 0, angle is +/-PI_2, depending on y
    {
        if (y >= 0.0f) return  F_PI_2;
        else           return -F_PI_2;
    }

    float v;    // our angle, our value

    const int inv = (int)(absx < absy);

    if (inv)  v = absx/absy;    // invert ratio if y > x in order to make sure
    else      v = absy/absx;    // the ratio remains in the valid range [0,1]

    // source: Fast approximate arctan/atan function - http://nghiaho.com/?p=997
    // angle = F_PI_4*v - v*(fabsf(v) - 1.0f)*(0.2447f + 0.0663f*fabsf(v));
    //
    // simplification & restriction...
    // y = 0.785398163397448309616*v - v*(abs(v) - 1.0)*(0.2447 + 0.0663*abs(v))
    // y = v * (0.785398 - ((abs(v) - 1.0)*(0.2447 + 0.0663*abs(v))))
    // y = v * (0.785398 - 0.2447*abs(v) - 0.0663*v*v + 0.2447 + 0.0663*abs(v))
    // y = v * (1.030098 - 0.1784*abs(v) - 0.0663*v*v)
    // y = v * (1.030098 - 0.1784*v - 0.0663*v*v)   // breaks [-1,0], not [0,1]
    // y = v * (1.030098 + v * ((-0.1784) + v * (-0.0663)))

    const float c1 = 1.00535535812377930000f;  //  1.030098f
    const float c2 =-0.08889085054397583000f;  // -0.178400f
    const float c3 =-0.13527311384677887000f;  // -0.066300f

    v = v*(c1 + v*(c2 + v*(c3)));   // compute angle

    if (inv)  v = F_PI_2 - v;       // if inverse ratio, complementary angle

    const int y_neg = (int)(y < 0);
    const int x_neg = (int)(x < 0);

    if (y_neg)  v = -v;     // if y is negative, flip sign of angle

    if (x_neg)              // if x is negative, supplementary angle
    {
        if (y_neg)  return -F_PI - v;
        else        return  F_PI - v;
    }

    return v;
}

void fast_math_init()
{
    union { float f; unsigned int u; } i;
    unsigned int u;
    
    for (u=0; u<=0x7FFF; u++)
    {
        // Build a float with the bit pattern u as mantissa
        //  and an exponent of 0, stored as 127
        i.u = (u << 8) | (0x7F << 23);
        i.f = (float)sqrt(i.f);
        
        // Take the square root then strip the first 7 bits of
        //  the mantissa into the table
        fast_sqrtf_lut[u + 0x8000] = (i.u & 0x7FFFFF);
        
        // Repeat the process, this time with an exponent of 1, 
        //  stored as 128
        i.u = (u << 8) | (0x80 << 23);
        i.f = (float)sqrt(i.f);
        
        fast_sqrtf_lut[u] = (i.u & 0x7FFFFF);
    }
}

float fast_sqrtf(float v)   // Paul Hsieh, http://www.azillionmonkeys.com/qed/sqroot.html
{
    union { float f; unsigned int u; } i = {v};
    
    if (i.u == 0)    return 0.0;     // check for square root of 0
    
    unsigned int dlo =     0xFFFF;
    unsigned int bm0 = 0x3F800000;  // 00111111100000000000000000000000
    unsigned int bm1 = 0x7F800000;  // 01111111100000000000000000000000
    
    i.u = fast_sqrtf_lut[(i.u >> 8) & dlo] | ((((i.u - bm0) >> 1) + bm0) & bm1);
    
    return i.f;
}

/*
float fast_sqrtf(float v)   // DOES NOT WORK ON NIOS II
{
    unsigned int* p = (unsigned int*) &v;
    
    if (*p == 0)    return 0.0;     // check for square root of 0
    
    unsigned int dlo =     0xFFFF;
    unsigned int bm0 = 0x3F800000;  // 00111111100000000000000000000000
    unsigned int bm1 = 0x7F800000;  // 01111111100000000000000000000000
    
    *p = fast_sqrtf_lut[(*p >> 8) & dlo] | ((((*p - bm0) >> 1) + bm0) & bm1);
    
    return v;
}
*/

float fast_invsqrtf(float v)    // Jan Kaldec, http://rrrola.wz.cz/inv_sqrt.html
{
    union { float f; unsigned int u; } s = {v};
    s.u = 0x5F1FFFF9ul - (s.u >> 1);
    return 0.703952253f * s.f * (2.38924456f - v * s.f * s.f);
}



int is_big_endian()
{
	union {char c[2]; short s;} i;
	i.c[0] = (char)1;
	i.c[1] = (char)0;
	return i.s != 1;
}

void benchmark(void)
{
	uint32_t t = UPTIME;

	printf("endianness: %s endian\r", is_big_endian() ? "big" : "little");

	printf("***Start Benchmark***\r");
	int i;
	double r_d = 0.0;
	float  r_f = 0.0f;
	int    r_i = 0;

	#define CNT 1000

	int    val_i[CNT+1];
	float  val_f[CNT+1];
	double val_d[CNT+1];
	int    abs_i[CNT+1];
	float  abs_f[CNT+1];
	double abs_d[CNT+1];
  srand(time(0));
	for(i = 0; i < CNT+1; i++)
	{
		double v = rand()/3.21;
    if (fabs(v) < 1.0) { i--; continue; }
		val_i[i] = (int)v;
		val_f[i] = (float)v;
		val_d[i] = v;
		abs_i[i] = fabs((int)v);
		abs_f[i] = fabsf((float)v);
		abs_d[i] = fabs(v);
	}

	// max relative error tests
	double mre_sqrtf   = 0.0;
	double mre_sqrtff  = 0.0;
	double mre_sinf    = 0.0;
	double mre_sinff   = 0.0;
	double mre_cosf    = 0.0;
	double mre_cosff   = 0.0;
	double mre_atan2f  = 0.0;
	double mre_atan2ff = 0.0;
    double tol = 1e-8;          // tolerance
	// sqrt
	for(i=0; i<CNT; i++)
	{
		double d = sqrt(abs_d[i]);
		float f = sqrtf(abs_f[i]);
		float ff = fast_sqrtf(abs_f[i]);

		if (fabs(f -d) < tol) continue;    // too small difference, skip
		if (fabs(ff-d) < tol) continue;    // too small difference, skip
		if (fabs(d) < tol) continue;       // too small divider, skip

		double re_f  = fabs(1.0 - (double)f /(double)d);
		double re_ff = fabs(1.0 - (double)ff/(double)d);

		if (re_f  > mre_sqrtf ) mre_sqrtf  = re_f;
		if (re_ff > mre_sqrtff) mre_sqrtff = re_ff;
	}
	// sin
	for(i=0; i<CNT; i++)
	{
		double d = sin(val_d[i]);
		float f = sinf(val_f[i]);
		float ff = fast_sinf(val_f[i]);

		if (fabs(f -d) < tol) continue;    // too small difference, skip
		if (fabs(ff-d) < tol) continue;    // too small difference, skip
		if (fabs(d) < tol) continue;       // too small divider, skip

		double re_f  = fabs(1.0 - (double)f /(double)d);
		double re_ff = fabs(1.0 - (double)ff/(double)d);

		if (re_f  > mre_sinf ) mre_sinf  = re_f;
		if (re_ff > mre_sinff) mre_sinff = re_ff;
	}
	// cos
	for(i=0; i<CNT; i++)
	{
		double d = cos(val_d[i]);
		float f = cosf(val_f[i]);
		float ff = fast_cosf(val_f[i]);

		if (fabs(f -d) < tol) continue;    // too small difference, skip
		if (fabs(ff-d) < tol) continue;    // too small difference, skip
		if (fabs(d) < tol) continue;       // too small divider, skip

		double re_f  = fabs(1.0 - (double)f /(double)d);
		double re_ff = fabs(1.0 - (double)ff/(double)d);

		if (re_f  > mre_cosf ) mre_cosf  = re_f;
		if (re_ff > mre_cosff) mre_cosff = re_ff;
	}
	// atan2
	for(i=0; i<CNT; i++)
	{
		double d = atan2(val_d[i], val_d[i+1]);
		float f = atan2f(val_f[i], val_f[i+1]);
		float ff = fast_atan2f(val_f[i], val_f[i+1]);

		if (fabs(f -d) < tol) continue;    // too small difference, skip
		if (fabs(ff-d) < tol) continue;    // too small difference, skip
		if (fabs(d) < tol) continue;       // too small divider, skip

		double re_f  = fabs(1.0 - (double)f /(double)d);
		double re_ff = fabs(1.0 - (double)ff/(double)d);

		if (re_f  > mre_atan2f ) mre_atan2f  = re_f;
		if (re_ff > mre_atan2ff) mre_atan2ff = re_ff;
	}

	printf("Each function called %d times\r", i);

	for(t=UPTIME, i=0; i<CNT; i++) r_d = val_d[i] * val_d[i+1];
	printf("     mul (double)     : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = val_f[i] * val_f[i+1];
	printf("     mul (float)      : %7lu us, %f\r", UPTIME-t, r_f);

	for(t=UPTIME, i=0; i<CNT; i++) r_i = val_i[i] * val_i[i+1];
	printf("     mul (int)        : %7lu us, %i\r", UPTIME-t, r_i);


	for(t=UPTIME, i=0; i<CNT; i++) r_d = val_d[i] / val_d[i+1];
	printf("     div (double)     : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = val_f[i] / val_f[i+1];
	printf("     div (float)      : %7lu us, %f\r", UPTIME-t, r_f);

	for(t=UPTIME, i=0; i<CNT; i++) r_i = val_i[i] / val_i[i+1];
	printf("     div (int)        : %7lu us, %i\r", UPTIME-t, r_i);


	for(t=UPTIME, i=0; i<CNT; i++) r_d = fabs(val_d[i]);
	printf("     fabs (double)    : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fabsf(val_f[i]);
	printf("     fabsf (float)    : %7lu us, %f\r", UPTIME-t, r_f);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fast_fabsf(val_f[i]);
	printf("fast_fabsf (float)    : %7lu us, %f\r", UPTIME-t, r_f);


	for(t=UPTIME, i=0; i<CNT; i++) r_d = sqrt(abs_d[i]);
	printf("     sqrt (double)    : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = sqrtf(abs_f[i]);
	printf("     sqrtf (float)    : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_sqrtf);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fast_sqrtf(abs_f[i]);
	printf("fast_sqrtf (float)    : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_sqrtff);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fast_invsqrtf(abs_f[i]);
	printf("fast_invsqrtf (float) : %7lu us, %f\r", UPTIME-t, r_f);


	for(t=UPTIME, i=0; i<CNT; i++) r_d = sin(val_d[i]);
	printf("     sin (double)     : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = sinf(val_f[i]);
	printf("     sinf (float)     : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_sinf);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fast_sinf(val_f[i]);
	printf("fast_sinf (float)     : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_sinff);


	for(t=UPTIME, i=0; i<CNT; i++) r_d = cos(val_d[i]);
	printf("     cos (double)     : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = cosf(val_f[i]);
	printf("     cosf (float)     : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_cosf);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fast_cosf(val_f[i]);
	printf("fast_cosf (float)     : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_cosff);


	for(t=UPTIME, i=0; i<CNT; i++) r_d = atan2(val_d[i], val_d[i+1]);
	printf("     atan2 (double)   : %7lu us, %f\r", UPTIME-t, r_d);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = atan2f(val_f[i], val_f[i+1]);
	printf("     atan2f (float)   : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_atan2f);

	for(t=UPTIME, i=0; i<CNT; i++) r_f = fast_atan2f(val_f[i], val_f[i+1]);
	printf("fast_atan2f (float)   : %7lu us, %f (%lf %%)\r", UPTIME-t, r_f, 100.0*mre_atan2ff);

	printf("*** End Benchmark ***\r");
}
/* Test du 24 avril
***Start Benchmark***
dot (double) 1000 times:13257 us
dot (int) 1000 times:243 us
dot (float) 1000 times:2697 us
divide (double) 1000 times:22387 us
divide (int) 1000 times:268 us
divide (float) 1000 times:8113 us
sqrt (double) 1000 times:18404 us
sqrt (float) 1000 times:7820 us
sin (double) 1000 times:149762 us
sinf (float) 1000 times:66097 us
atan2 (double) 1000 times:259504 us
atan2f (float) 1000 times:98125 us
***End Benchmark**
***End **/
