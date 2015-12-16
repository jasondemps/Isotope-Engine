#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>

typedef float real;

namespace Math
{
  // Typedefs for consistency
  typedef unsigned char      u8;
  typedef char               s8;
  typedef unsigned int       u32;
  typedef int                s32;
  typedef unsigned long long u64;
  typedef long long          s64;
  typedef float              f32;
  typedef double             f64;

  

  // Do not change
  static const f32 EPSILON = 0.0001f;
  static const f32 PI = 3.1415926535897932384626433832795f;
  static const f32 DegRad = PI / 180.f;
  static const f32 RadDeg = 180.f / PI;
}

#endif