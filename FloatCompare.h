#pragma once



#ifndef _FLOATCMP
#define _FLOATCMP



// Includes

#include <float.h>
#include <math.h>
#include <stdbool.h>



// Public



// Macros

typedef double float64;



// Functions

bool Float64_ApproxEqual(float64 _first, float64 _second);

bool Float64_ApproxGreater(float64 _first, float64 _second);

bool Float64_ApproxLess(float64 _first, float64 _second);

#endif _FLOATCMP