#ifndef __SC_MATH_H__
#define __SC_MATH_H__

extern float sc_math_sin(float x);
extern float sc_math_cos(float x);
extern float sc_math_tan(float x);
extern float sc_math_asin(float x);
extern float sc_math_acos(float x);
extern float sc_math_atan(float x);
extern float sc_math_atan2(float y, float x);

extern float sc_math_invsqrt(float x);
extern float sc_math_mac(float x, float y, float z);
extern float sc_math_sum_N(float* x, unsigned char n);
extern float sc_math_sub_N(float* x, unsigned char n);
extern float sc_math_prdct(float* x, unsigned char n);
extern float sc_math_sumsq(float* x, unsigned char n);

#endif
