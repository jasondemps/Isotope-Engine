#include "Vector4.h"

namespace Math
{
  const Vector4 Vector4::UnitX = Math::Vector4(1, 0, 0);
  const Vector4 Vector4::UnitY = Math::Vector4(0, 1, 0);
  const Vector4 Vector4::UnitZ = Math::Vector4(0, 0, 1);
  const Vector4 Vector4::Zero  = Math::Vector4(0, 0, 0);
  const Vector4 Vector4::One   = Math::Vector4(1, 1, 1);

  void Vector4::Print(void) const
  {
    printf("%5.3f, %5.3f, %5.3f, %5.3f\n",x,y,z,w);
  }

  // Default constructor, initializes x,y,z to zeroes, w to defined value
  Vector4::Vector4(void) : x(0), y(0), z(0), w(0.f)
  {}
  
    // Copy constructor, copies every component from the other Vector4
  Vector4::Vector4(const Vector4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
  {}
  
    // Non-Default constructor, self explanatory
  Vector4::Vector4(f32 xx, f32 yy, f32 zz, f32 ww) : x(xx), y(yy), z(zz), w(ww)
  {}
  
    // Assignment operator, does not need to handle self assignment
  Vector4& Vector4::operator=(const Vector4& rhs)
  {
    if (this == &rhs)
      return *this;

    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;

    return *this;
  }
  
    // Unary negation operator, negates all components and returns a copy
  Vector4 Vector4::operator-(void) const
  {
    return Vector4(x * -1, y * -1, z * -1, w * -1);
  }

    // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A 
    // from Vector B, or multiply a vector with a scalar, or divide a vector by 
    // that scalar
  Vector4 Vector4::operator+(const Vector4& rhs) const
  {
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
  }
  
  Vector4 Vector4::operator-(const Vector4& rhs) const
  {
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
  }
  
  Vector4 Vector4::operator*(const f32 rhs) const
  {
    return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
  }
  
  Vector4 Vector4::operator/(const f32 rhs) const
  {
    return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
  }
  
  
    // Same as above, just stores the result in the original vector
  Vector4& Vector4::operator+=(const Vector4& rhs)
  {
    x += rhs.x; 
    y += rhs.y; 
    z += rhs.z;
    w += rhs.w;

    return *this;
  }
  
  Vector4& Vector4::operator-=(const Vector4& rhs)
  {
    x -= rhs.x; 
    y -= rhs.y; 
    z -= rhs.z;
    w -= rhs.w;

    return *this;
  }
  
  Vector4& Vector4::operator*=(const f32 rhs)
  {
    x *= rhs; 
    y *= rhs; 
    z *= rhs;
    w *= rhs;

    return *this;
  }
  
  Vector4& Vector4::operator/=(const f32 rhs)
  {
    x /= rhs; 
    y /= rhs; 
    z /= rhs;
    w /= rhs;

    return *this;
  }
  
  
    // Comparison operators which should use an epsilon defined in 
    // Utilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
  bool Vector4::operator==(const Vector4& rhs) const
  {
    for (int i = 0; i < 4; ++i)
    {
      f32 s = v[i] - rhs.v[i];

      if (s > EPSILON || s < -EPSILON)
        return false;
    }

    return true;
  }
  
  bool Vector4::operator!=(const Vector4& rhs) const
  {
    return !(*this == rhs);
  }

  void Vector4::Set(f32 x_, f32 y_, f32 z_)
  {
    x_ = x; y_ = y; z_ = z;
  }
  
    // Computes the dot product with the other vector. Treat it as 3D vector.
  f32 Vector4::Dot(const Vector4& rhs) const
  {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  
    // Computes the cross product with the other vector. Treat it as a 3D vector.
  Vector4 Vector4::Cross(const Vector4& rhs) const
  {
    return Vector4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }
  
    // Computes the true length of the vector 
  f32 Vector4::Length(void) const
  {
    return sqrt((x * x) + (y * y) + (z * z) + (w * w));
  }
  
    // Computes the squared length of the vector
  f32 Vector4::LengthSq(void) const
  {
    return (x * x) + (y * y) + (z * z) + (w * w);
  }
  
    // Normalizes the vector to make the final vector be of length 1. If the length is zero
    // then this function should not modify anything.
  Vector4 Vector4::Normalize(void)
  {
    f32 len = Length();

    if (len == 0.f)
      return Vec4::Zero;

    return Vec4(x / len, y / len, z / len, w / len);
  }
  
  Vector4 Vector4::Midpoint(const Vector4 &v1, const Vector4 &v2)
  {
    return Vector4((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, 0);
  }

  Vector4 Vector4::Midpoint(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3)
  {
    return Vector4((v1.x + v2.x + v3.x) / 3, (v1.y + v2.y + v3.y) / 3, (v1.z + v2.z + v3.z) / 3);
  }


  Vector4 Vector4::WeightedMidpoint(const Vector4 &v1, const Vector4 &v2, real weight)
  {
    real x = (v1.x * weight) + (v2.x * (1 - weight));
    real y = (v1.y * weight) + (v2.y * (1 - weight));

    return Vector4(x, y, 0);
  }

  //Vector4 Vector4::WeightedMidpoint(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, real weight)
  //{
  //	real x = (v1.x * weight) + (v2.x * (1 - weight));
  //	real y = (v1.y * weight) + (v2.y * (1 - weight));
  //	real y = (v1.z * weight) + (v2.z * (1 - weight));

  //	return Vector4(x, y);
  //}

  real Vector4::Angle(void) const
  {
    return atan2(-y, x);
  }

  real Vector4::AngleBetween(const Vector4 &rhs) const
  {
    return (*this - rhs).Angle();
  }

  real Vector4::AngleBetween(const Vector4 &vec1, const Vector4 &vec2) const
  {
    return (vec1 - vec2).Angle();
  }

  real Vector4::AngleOfVector(void) const
  {
    return atan2(-y, x);
  }

  /*
  real Vector4::Dot(const Vector4 &other) const
  {
    return x * other.x + y * other.y + z * other.z;
  }
  */
  const Vector4 Vector4::Cross(real X, real Y, real Z) const
  {
    return Vector4(y * Z - z * Y, z * X - x * Z, x * Y - y * X);
  }

  real Vector4::Cross2D(const Vector4 &other) const
  {
    return (x * other.y) - (y * other.x);
  }

  real Vector4::Cross2D(real X, real Y) const
  {
    return (x * Y) - (y * X);
  }

  real Vector4::Magnitude(void) const
  {
    return std::sqrt(x * x + y * y + z * z);
  }
  
  real Vector4::AngleX(void) const
  {
    return std::atan2(z, y);
  }

  real Vector4::AngleY(void) const
  {
    return std::atan2(x, z);
  }

  real Vector4::AngleZ(void) const
  {
    return std::atan2(y, x);
  }

  real Vector4::Distance(const Vector4 &other) const
  {
    return Distance(other.x, other.y, other.z);
  }

  real Vector4::Distance(real x, real y, real z) const
  {
    real dX = x - x;
    real dY = y - y;
    real dZ = z - z;

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
  }

  real Vector4::DistanceSquared(const Vector4 &other) const
  {
    return DistanceSquared(other.x, other.y, other.z);
  }

  real Vector4::DistanceSquared(real x, real y, real z) const
  {
    real dX = x - x;
    real dY = y - y;
    real dZ = z - z;

    return dX * dX + dY * dY + dZ * dZ;
  }
  
  Vector4 Vector4::GetReflectedVector(const Vector4 & vec)
  {
    Vector4 reflected;

    real dot = Dot(vec);

    reflected.x = 2 * dot * vec.x - x;
    reflected.y = 2 * dot * vec.y - y;

    return reflected;
  }

  //Project a onto b. In this case, a is "this" and b is the paramater
  const Vector4 Vector4::ProjectOntoVector(const Vector4 &rhs)
  {
    //projection of b onto a (rhs onto this)
    // (  a * b )
    // ( -------) * a
    // ( |a||a| )
    real scalar = (Dot(rhs) / (rhs.Magnitude() * rhs.Magnitude()));
    return *this * scalar;
  }

  bool Vector4::CheckTwoVectorsAreParallel(const Vector4 &vec2D)
  {
    return (Cross2D(vec2D) == 0);
  }

  bool Vector4::CheckTwoVectorsArePerpendicular(const Vector4 &vec)
  {
    return (Dot(vec) == 0);
  }

  const Vector4 Vector4::Towards(const Vector4 &v1, const Vector4 &v2)
  {
    return v2 - v1;
  }

  const Vector4 Vector4::Towards(real x1, real y1, real z1, real x2, real y2, real z2)
  {
    return Vector4(x2 - x1, y2 - y1, z2 - z1);
  }

  //---------- Function FromAngleX ----------
  //  Description: 
  //      Creates a Vector4 rotated an amount of radians about the x-axis.
  //
  //  Parameter radians:
  //      The amount of radians to rotate.
  //
  //  Parameter length:
  //      The length of the resulting Vector4.
  //-------------------------------------
  const Vector4 Vector4::FromAngleX(real radians, real length)
  {
    return Vector4(0, std::cos(radians) * length, std::sin(radians) * length);
  }


  //---------- Function FromAngleY ----------
  //  Description: 
  //      Creates a Vector4 rotated an amount of radians about the y-axis.
  //
  //  Parameter radians:
  //      The amount of radians to rotate.
  //
  //  Parameter length:
  //      The length of the resulting Vector4.
  //-------------------------------------
  const Vector4 Vector4::FromAngleY(real radians, real length)
  {
    return Vector4(std::sin(radians) * length, 0, std::cos(radians) * length);
  }

  //---------- Function FromAngleZ ----------
  //  Description: 
  //      Creates a Vector4 rotated an amount of radians about the z-axis.
  //
  //  Parameter radians:
  //      The amount of radians to rotate.
  //
  //  Parameter length:
  //      The length of the resulting Vector4.
  //-------------------------------------
  const Vector4 Vector4::FromAngleZ(real radians, real length)
  {
    return Vector4(std::cos(radians) * length, std::sin(radians) * length, 0);
  }


  //---------- Function Orthonormalize ----------
  //  Description: 
  //      Orthonormalizes a set of Vector4s, making them mutually
  //      orthogonal and of length 1.
  //
  //  Parameter v1:
  //      The first Vector4 of the set.
  //
  //  Parameter v2:
  //      The second Vector4 of the set.
  //
  //  Parameter v3:
  //      The third Vector4 of the set.
  //-------------------------------------
  void Vector4::Orthonormalize(Vector4 &v1, Vector4 &v2, Vector4 &v3)
  {
    //Uses the Gram-Schmidt process of orthonormalization

    real dot1;
    real dot2;

    v1.Normalize();

    dot1 = v1.Dot(v2);
    v2 -= v1 * dot1;
    v2.Normalize();

    dot1 = v1.Dot(v3);
    dot2 = v2.Dot(v3);
    v3 -= v1 * dot1 + v2 * dot2;
    v3.Normalize();
  }

  //---------- Function GenerateOrthonormalBasis ----------
  //  Description: 
  //      Generates a basis of orthonormalized Vector4s given an initial Vector4.
  //
  //  Parameter intial:
  //      The intial Vector4 to generate the remainder of the basis from. initial 
  //      will be normalized during the execution of this function. Use
  //      GenerateComplementBasis if initial is already normalized.
  //
  //  Parameter v1:
  //      A reference to a Vector4 used to store the second axis of the basis.
  //
  //  Parameter v2:
  //      A reference to a Vector4 used to store the third axis of the basis.
  //-------------------------------------
  void Vector4::GenerateOrthonormalBasis(Vector4 &initial, Vector4 &v1, Vector4 &v2)
  {
    GenerateComplementBasis(initial.Normalize(), v1, v2);
  }

  //---------- Function GenerateComplementBasis ----------
  //  Description: 
  //      Generates a basis of orthonormalized Vector4s given an initial Vector4.
  //
  //  Parameter intial:
  //      The intial Vector4 to generate the remainder of the basis from. initial 
  //      must be a unit vector.
  //
  //  Parameter v1:
  //      A reference to a Vector4 used to store the second axis of the basis.
  //
  //  Parameter v2:
  //      A reference to a Vector4 used to store the third axis of the basis.
  //-------------------------------------
  void Vector4::GenerateComplementBasis(Vector4 &initial, Vector4 &v1, Vector4 &v2)
  {
    if (std::abs(initial.x) >= std::abs(initial.y))
    {
      real invLength = 1.0f / std::sqrt(initial.x * initial.x + initial.z * initial.z);

      v1 = Vector4(-initial.z * invLength, 0.0f, initial.x * invLength);
      v2 = Vector4(initial.y * v1.z, initial.z * v1.x - initial.x * v1.z, -initial.y * v1.x);
    }

    else
    {
      real invLength = 1.0f / std::sqrt(initial.y * initial.y + initial.z * initial.z);

      v1 = Vector4(0.0f, initial.z * invLength, -initial.y * invLength);
      v2 = Vector4(initial.y * v1.z - initial.z * v1.y, -initial.x * v1.z, initial.x * v1.y);
    }
  }

  Vector4 operator*(real lhs, Vector4& rhs)
  {
    return rhs * lhs;
  }
}