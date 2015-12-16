#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "MathUtils.h"

namespace Math
{
  struct Vector4
  {
    union
    {
      struct 
      {
        f32 x, y, z, w;
      };
  
      struct  
      {
        f32 r, g, b, a;
      };
  
      f32 v[4];
    };
  
    /* 
      This union lets us access the data in multiple ways
      All of these are modifying the same location in memory
  
      Vector4 vec;
      vec.z = 1.0f;
      vec.b = 2.0f;
      vec.v[2] = 3.0f;
    */
  
      // Default constructor, initializes x,y,z to zeroes, w to defined value
    Vector4(void);
  
      // Copy constructor, copies every component from the other Vector4
    Vector4(const Vector4& rhs);
  
      // Non-Default constructor, self explanatory
    Vector4(f32 xx, f32 yy, f32 zz = 0.f, f32 ww = 0.0f);
  
      // Assignment operator, does not need to handle self assignment
    Vector4& operator=(const Vector4& rhs);
  
      // Unary negation operator, negates all components and returns a copy
    Vector4 operator-(void) const;  
    
      // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A 
      // from Vector B, or multiply a vector with a scalar, or divide a vector by 
      // that scalar
    Vector4 operator+(const Vector4& rhs) const;
    Vector4 operator-(const Vector4& rhs) const;
    Vector4 operator*(const f32 rhs) const;
    Vector4 operator/(const f32 rhs) const;
  
      // Same as above, just stores the result in the original vector
    Vector4& operator+=(const Vector4& rhs);
    Vector4& operator-=(const Vector4& rhs);
    Vector4& operator*=(const f32 rhs);
    Vector4& operator/=(const f32 rhs);
  
      // Comparison operators which should use an epsilon defined in 
      // Utilities.h to see if the value is within a certain range
      // in which case we say they are equivalent.
    bool operator==(const Vector4& rhs) const;
    bool operator!=(const Vector4& rhs) const;
  
      // Computes the dot product with the other vector. Treat it as 3D vector.
    f32 Dot(const Vector4& rhs) const;
  
      // Computes the cross product with the other vector. Treat it as a 3D vector.
    Vector4 Cross(const Vector4& rhs) const;
  
      // Computes the true length of the vector 
    f32 Length(void) const;
  
      // Computes the squared length of the vector
    f32 LengthSq(void) const;
  
      // Normalizes the vector to make the final vector be of length 1. If the length is zero
      // then this function should not modify anything.
    Vector4 Normalize(void);
  
      // Already implemented, simple print function
    void Print(void) const;

    void Set(f32 x_, f32 y_, f32 z_ = 0.f);

    Vector4 Midpoint(const Vector4 &v1, const Vector4 &v2);
    Vector4 Midpoint(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3);
    Vector4 WeightedMidpoint(const Vector4 &v1, const Vector4 &v2, real weight);
    //Vector4 WeightedMidpoint(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, real weight);


    real Angle() const; //Assuming 2D
    real AngleBetween(const Vector4 &rhs) const; 
    real AngleBetween(const Vector4 &vec1, const Vector4 &vec2) const; 
    real AngleOfVector(void) const; //Assuming 2D
    const Vector4 Cross(real X, real Y, real Z) const;
    real Cross2D(const Vector4 &other) const;
    real Cross2D(real X, real Y) const;
    
    real Magnitude(void) const;
    real AngleX(void) const;
    real AngleY(void) const;
    real AngleZ(void) const;
    real Distance(const Vector4 &other) const;
    real Distance(real x, real y, real z) const;
    real DistanceSquared(const Vector4 &other) const;
    real DistanceSquared(real x, real y, real z) const;

    Vector4 GetReflectedVector(const Vector4 &rhs);
    const Vector4 ProjectOntoVector(const Vector4 &rhs); //Project a onto b. In this case, a is "this" and b is the paramater

    bool CheckTwoVectorsAreParallel(const Vector4 &vec2D);
    bool CheckTwoVectorsArePerpendicular(const Vector4 &rhs);

    //--------------------------------------------------------------------------------
    //                          Static methods
    //--------------------------------------------------------------------------------
    static real Dot(const Vector4 &vec1, const Vector4 &vec2);
    static real Cross2D(const Vector4 &vec1, const Vector4 &vec2);
    static real Cross2D(real X1, real Y1, real X2, real Y2);
    static const Vector4 Towards(const Vector4 &v1, const Vector4 &v2);
    static const Vector4 Towards(real x1, real y1, real z, real x2, real y2, real z2);
    static const Vector4 FromAngleX(real radians, real length = 1.0f);
    static const Vector4 FromAngleY(real radians, real length = 1.0f);
    static const Vector4 FromAngleZ(real radians, real length = 1.0f);

    static void Orthonormalize(Vector4 &v1, Vector4 &v2, Vector4 &v3);
    static void GenerateOrthonormalBasis(Vector4 &initial, Vector4 &v1, Vector4 &v2);
    static void GenerateComplementBasis(Vector4 &initial, Vector4 &v1, Vector4 &v2);

    static const Vector4 UnitX;
    static const Vector4 UnitY;
    static const Vector4 UnitZ;
    static const Vector4 Zero;
    static const Vector4 One;
  };

  Vector4 operator*(real lhs, Vector4& rhs);

  typedef Vector4 Vec4;
}

#endif