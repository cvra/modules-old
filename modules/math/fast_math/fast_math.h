/* File        : modules/math/fast_math/fast_math.h
 * Author      : Mathieu Rouvinez
 * Project     : CVRA Robot #1, SwissRobot 2012
 * State       : appears to work
 * Creation    : 2012.04.24  (yes, YYYY.MM.DD, because it's logical)
 * Last modif. : 2012.04.27
 * Description : quite fast math function, accurate enough, nothing more
 * Notes       : some code borrowed from other programmers, didn't ask them...
 * Disclaimer  : works on my machine, check if it does on your machine too
 * Copyright   : none in my opinion, tell everyone
 */

#include <math.h>

#define M_PI   3.14159265358979323846f
#define M_PI_2 1.57079632679489661923f
#define M_PI_4 0.785398163397448309616f
#define M_1_PI 0.318309886183790671538f
#define M_2_PI 0.636619772367581343076f


// DECLARATIONS

static unsigned int fast_sqrtf_lut[0x10000];    // fast_sqrtf lookup table

void  fast_math_init();     //################# DO NOT FORGET #################

float fast_fabsf    (float v);
float fast_sinf     (float v);
float fast_cosf     (float v);
float fast_atan2f   (float y, float x);
float fast_sqrtf    (float v);
float fast_invsqrtf (float v);


// DEFINITIONS

inline float fast_fabsf(float v)
{
    unsigned int* p = (unsigned int*) &v;   // pointer, for aliasing
    *p &= 0x7FFFFFFFu;                      // bitmask, set MSB to 0
    return v;                               // done, neat !
}

float fast_sinf(float v)    // ref: http://dotancohen.com/eng/taylor-sine.php
{
    int q = -(int)(v<0.0f);     // get number of shifts from quadrant I
    q = q + (int)(v*M_2_PI);    // get number of shifts from quadrant I
    v = v - (float)(q)*M_PI_2;  // our angle now fits in the range [0,PI_2]
    
    q = q&3;    // quadrant number = number of quadrant shifts modulo 4
    
    if (q==1 || q==3) v = M_PI_2 - v;   // quad II or IV, complementary angle
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
    q = q + (int)(v*M_2_PI);    // get number of shifts from quadrant I
    v = v - (float)(q)*M_PI_2;  // our angle now fits in the range [0,PI_2]
    
    q = q&3;    // quadrant number = number of quadrant shifts modulo 4
    
    float s = 1.0f;     // multiplicator, flipping or not the sign of the cos
    
    if (q==1 || q==3) v = M_PI_2 - v;   // quad II or IV, complementary angle
    if (q==1 || q==2) s = -1.0f;        // quad II or III, flip sign of cos
    
    const float v2 = v*v;
    const float c1 = 0.99903213977813721000f;  //  1.000000f ~= 1/0! = 1/1
    const float c2 =-0.49264952540397644000f;  // -0.500000f ~= 1/2! = 1/2
    const float c3 = 0.03556701540946960400f;  //  0.041667f ~= 1/4! = 1/24
    
    return s*(c1+v2*(c2+v2*(c3)));  // compute Taylor series terms and return
}

float fast_atan2f(float y, float x)
{
    const float absy = fast_fabsf(y);
    const float absx = fast_fabsf(x);
    
    if (absy < 1e-5f)   // if y near 0, angle is 0 or PI, depending on x
    {
        if (x >= 0.0f) return 0.0f;
        else           return M_PI;
    }
    
    if (absx < 1e-5f)   // if x near 0, angle is +/-PI_2, depending on y
    {
        if (y >= 0.0f) return  M_PI_2;
        else           return -M_PI_2;
    }
    
    float v;    // our angle, our value
    
    const int inv = (int)(absx < absy);
    
    if (inv)  v = absx/absy;    // invert ratio if y > x in order to make sure
    else      v = absy/absx;    // the ratio remains in the valid range [0,1]
    
    // source: Fast approximate arctan/atan function - http://nghiaho.com/?p=997
    // angle = M_PI_4*v - v*(fabsf(v) - 1.0f)*(0.2447f + 0.0663f*fabsf(v));
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
    
    if (inv)  v = M_PI_2 - v;       // if inverse ratio, complementary angle
    
    const int y_neg = (int)(y < 0);
    const int x_neg = (int)(x < 0);
    
    if (y_neg)  v = -v;     // if y is negative, flip sign of angle
    
    if (x_neg)              // if x is negative, supplementary angle
    {
        if (y_neg)  return -M_PI - v;
        else        return  M_PI - v;
    }
    
    return v;
}

void fast_math_init()
{
    union { float f; unsigned int u; } s;
    
    for (unsigned int u=0; u<=0x7FFF; u++)
    {
        // Build a float with the bit pattern u as mantissa
        //  and an exponent of 0, stored as 127
        s.u = (u << 8) | (0x7F << 23);
        s.f = (float)sqrt(s.f);
        
        // Take the square root then strip the first 7 bits of
        //  the mantissa into the table
        fast_sqrtf_lut[u + 0x8000] = (s.u & 0x7FFFFF);
        
        // Repeat the process, this time with an exponent of 1, 
        //  stored as 128
        s.u = (u << 8) | (0x80 << 23);
        s.f = (float)sqrt(s.f);
        
        fast_sqrtf_lut[u] = (s.u & 0x7FFFFF);
    }
}

float fast_sqrtf(float v)   // Paul Hsieh, http://www.azillionmonkeys.com/qed/sqroot.html
{
    unsigned int* p = (unsigned int*) &v;
    
    if (*p == 0)    return 0.0;     // check for square root of 0
    
    unsigned int dlo =     0xFFFF;
    unsigned int bm0 = 0x3F800000;  // 00111111100000000000000000000000
    unsigned int bm1 = 0x7F800000;  // 01111111100000000000000000000000
    
    *p = fast_sqrtf_lut[(*p >> 8) & dlo] | ((((*p - bm0) >> 1) + bm0) & bm1);
    
    return v;
}

float fast_invsqrtf(float v)    // Jan Kaldec, http://rrrola.wz.cz/inv_sqrt.html
{
    union { float f; unsigned int u; } s = {v};
    s.u = 0x5F1FFFF9ul - (s.u >> 1);
    return 0.703952253f * s.f * (2.38924456f - v * s.f * s.f);
}
