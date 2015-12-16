#include "Matrix4.h"
#include "Vector4.h"
#include "Point4.h"

namespace Math
{
  void Matrix4::Print(void) const
  {
    printf("--------------------------\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", m00, m01, m02, m03 );
    printf("%5.3f %5.3f %5.3f %5.3f\n", m10, m11, m12, m13 );
    printf("%5.3f %5.3f %5.3f %5.3f\n", m20, m21, m22, m23 );
    printf("%5.3f %5.3f %5.3f %5.3f\n", m30, m31, m32, m33 );
    printf("--------------------------\n");
  }

  // Default constructor should initialize to Identity
  Matrix4::Matrix4(void)
  {
    /*
    for (int i = 0; i < 16; ++i)
      v[i] = 0.f;
      */

    Identity();
  }
  
    // Copy constructor, copies every entry from the other matrix.
  Matrix4::Matrix4(const Matrix4& rhs)
  {
    for (int i = 0; i < 16; ++i)
      v[i] = rhs.v[i];
  }
  
    // Non-default constructor, self-explanatory
  Matrix4::Matrix4(f32 mm00, f32 mm01, f32 mm02, f32 mm03,
          f32 mm10, f32 mm11, f32 mm12, f32 mm13,
          f32 mm20, f32 mm21, f32 mm22, f32 mm23,
          f32 mm30, f32 mm31, f32 mm32, f32 mm33) :
  m00(mm00), m01(mm01), m02(mm02), m03(mm03),
  m10(mm10), m11(mm11), m12(mm12), m13(mm13),
  m20(mm20), m21(mm21), m22(mm22), m23(mm23),
  m30(mm30), m31(mm31), m32(mm32), m33(mm33)
  {
  }
  
    // Assignment operator, does not need to handle self-assignment
  Matrix4& Matrix4::operator=(const Matrix4& rhs)
  {
    for (int i = 0; i < 16; ++i)
      v[i] = rhs.v[i];

    return *this;
  }
  
    // Multiplying a Matrix4 with a Vector4 or a Point4
  Vector4 Matrix4::operator*(const Vector4& rhs) const
  {
    return Vector4(
      m00 * rhs.x + m01 * rhs.y + m02 * rhs.z + m03 * rhs.w,// x
      m10 * rhs.x + m11 * rhs.y + m12 * rhs.z + m13 * rhs.w,// y
      m20 * rhs.x + m21 * rhs.y + m22 * rhs.z + m23 * rhs.w,// z
      m30 * rhs.x + m31 * rhs.y + m32 * rhs.z + m33 * rhs.w // w
      );
  }

  Point4 Matrix4::operator*(const Point4& rhs) const
  {
    return Point4(
      m00 * rhs.x + m01 * rhs.y + m02 * rhs.z + m03 * rhs.w,// x
      m10 * rhs.x + m11 * rhs.y + m12 * rhs.z + m13 * rhs.w,// y
      m20 * rhs.x + m21 * rhs.y + m22 * rhs.z + m23 * rhs.w,// z
      m30 * rhs.x + m31 * rhs.y + m32 * rhs.z + m33 * rhs.w // w
      );
  }
  
    // Basic Matrix arithmetic operations
  Matrix4 Matrix4::operator+(const Matrix4& rhs) const
  {
    return Matrix4(
      m00 + rhs.m00, m01 + rhs.m01, m02 + rhs.m02, m03 + rhs.m03,
      m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13,
      m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23,
      m30 + rhs.m30, m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33
      );
  }

  Matrix4 Matrix4::operator-(const Matrix4& rhs) const
  {
    return Matrix4(
      m00 - rhs.m00, m01 - rhs.m01, m02 - rhs.m02, m03 - rhs.m03,
      m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13,
      m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23,
      m30 - rhs.m30, m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33
      );
  }

  Matrix4 Matrix4::operator*(const Matrix4& rhs) const
  {
    Matrix4 mat;

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
      {
        float total = 0;

        for (int k = 0; k < 4; ++k)
          total += m[i][k] * rhs.m[k][j];

        mat.m[i][j] = total;
      }

    return mat;
  }
  
    // Similar to the three above except they modify
    // the original 
  Matrix4& Matrix4::operator+=(const Matrix4& rhs)
  {
    for (int i = 0; i < 16; ++i)
      v[i] += rhs.v[i];

    return *this;
  }

  Matrix4& Matrix4::operator-=(const Matrix4& rhs)
  {
    for (int i = 0; i < 16; ++i)
      v[i] -= rhs.v[i];

    return *this;
  }

  Matrix4& Matrix4::operator*=(const Matrix4& rhs)
  {
    return (*this = *this * rhs);
  }
  
    // Scale/Divide the entire matrix by a float
  Matrix4 Matrix4::operator*(const f32 rhs) const
  {
    return Matrix4(
      m00 * rhs, m01 * rhs, m02 * rhs, m03 * rhs,
      m10 * rhs, m11 * rhs, m12 * rhs, m13 * rhs,
      m20 * rhs, m21 * rhs, m22 * rhs, m23 * rhs,
      m30 * rhs, m31 * rhs, m32 * rhs, m33 * rhs
      );
  }

  Matrix4 Matrix4::operator/(const f32 rhs) const
  {
    return Matrix4(
      m00 / rhs, m01 / rhs, m02 / rhs, m03 / rhs,
      m10 / rhs, m11 / rhs, m12 / rhs, m13 / rhs,
      m20 / rhs, m21 / rhs, m22 / rhs, m23 / rhs,
      m30 / rhs, m31 / rhs, m32 / rhs, m33 / rhs
      );
  }
  
    // Same as previous 
  Matrix4& Matrix4::operator*=(const f32 rhs)
  {
    for (int i = 0; i < 16; ++i)
      v[i] *= rhs;

    return *this;
  }

  Matrix4& Matrix4::operator/=(const f32 rhs)
  {
    for (int i = 0; i < 16; ++i)
      v[i] /= rhs;

    return *this;
  }
  
    // Comparison operators which should use an epsilon defined in 
    // Utilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
  bool Matrix4::operator==(const Matrix4& rhs) const
  {
    for (int i = 0; i < 16; ++i)
    {
      f32 s = v[i] - rhs.v[i];

      if (s > EPSILON || s < -EPSILON)
        return false;
    }

    return true;
  }

  bool Matrix4::operator!=(const Matrix4& rhs) const
  {
    return !(*this == rhs);
  }

  // Tranpose the current matrix and return a new one
  Matrix4 Matrix4::Transpose() const
  {
    Matrix4 trans;

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
      {
        trans.m[i][j] = m[j][i];
      }

    return trans;
  }
  
    // Zeroes out the entire matrix
  void Matrix4::Zero(void)
  {
    for (int i = 0; i < 16; ++i)
      v[i] = 0;
  }
  
    // Builds the identity matrix
  void Matrix4::Identity(void)
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        m[i][j] = 0.f;
      }

      m[i][i] = 1.f;
    }
  }

  const Matrix4 Matrix4::ScalingMatrix(const Vector4 &scale)
  {
      return ScalingMatrix(scale.x, scale.y, scale.z);
  }

  const Matrix4 Matrix4::ScalingMatrix(float xScl, float yScl, float zScl)
  {
      return Matrix4(xScl, 0.0f, 0.0f, 0.0f,
                      0.0f, yScl, 0.0f, 0.0f,
                      0.0f, 0.0f, zScl, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f);
  }

  const Matrix4 Matrix4::RotationXMatrix(float radians)
  {
      float cosR = std::cos(radians);
      float sinR = std::sin(radians);

      return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, cosR, -sinR, 0.0f,
                      0.0f, sinR, cosR, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f);
  }

  const Matrix4 Matrix4::RotationYMatrix(float radians)
  {
      float cosR = std::cos(radians);
      float sinR = std::sin(radians);

      return Matrix4(cosR, 0.0f, sinR, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      -sinR, 0.0f, cosR, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f);
  }

  const Matrix4 Matrix4::RotationZMatrix(float radians)
  {
      float cosR = std::cos(radians);
      float sinR = std::sin(radians);

      return Matrix4(cosR, -sinR, 0.0f, 0.0f,
                      sinR, cosR, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f);
  }

  const Matrix4 Matrix4::RotationMatrix(float roll, float pitch, float yaw)
  {
      return RotationZMatrix(roll) * RotationYMatrix(pitch) * RotationXMatrix(yaw);
  }

  const Matrix4 Matrix4::RotationMatrix(const Vector4 &axis, float radians)
  {
      float cosR = std::cos(radians);
      float sinR = std::sin(radians);

      float oneMinusCos = 1.0f - cosR;

      float xSq = axis.x * axis.x;
      float ySq = axis.y * axis.y;
      float zSq = axis.z * axis.z;

      float xym = axis.x  *  axis.y  *  oneMinusCos;
      float xzm = axis.x * axis.z * oneMinusCos;
      float yzm = axis.y * axis.z * oneMinusCos;

      float xSin = axis.x * sinR;
      float ySin = axis.y * sinR;
      float zSin = axis.z * sinR;
    
      Matrix4 rot;

      rot.m[0][0] = (xSq * oneMinusCos) + cosR;
      rot.m[0][1] = xym - zSin;
      rot.m[0][2] = xzm + ySin;
      rot.m[0][3] = 0.0f;

      rot.m[1][0] = xym + zSin;
      rot.m[1][1] = (ySq * oneMinusCos) + cosR;
      rot.m[1][2] = yzm - xSin;
      rot.m[1][3] = 0.0f;

      rot.m[2][0] = xzm - ySin;
      rot.m[2][1] = yzm + xSin;
      rot.m[2][2] = (zSq * oneMinusCos) + cosR;
      rot.m[2][3] = 0.0f;

      rot.m[3][0] = 0.0f;
      rot.m[3][1] = 0.0f;
      rot.m[3][2] = 0.0f;
      rot.m[3][3] = 1.0f;

      return rot;
  }

  const Matrix4 Matrix4::TranslationMatrix(const Vector4 &translation)
  {
  return TranslationMatrix(translation.x, translation.y, translation.z);
  }

  const Matrix4 Matrix4::TranslationMatrix(float xTrans, float yTrans, float zTrans)
  {
      return Matrix4(1.0f, 0.0f, 0.0f, xTrans,
                      0.0f, 1.0f, 0.0f, yTrans,
                      0.0f, 0.0f, 1.0f, zTrans,
                      0.0f, 0.0f, 0.0f, 1.0f);
  }

  const Matrix4 Matrix4::PerspectiveMatrix(float fovY, float aspectRatio, float zNear, float zFar)
  {
    float tangent = tan( fovY / 2 * Math::DegRad );
    float height = zNear * tangent;
    float width = height * aspectRatio;

    // Set the frustum matrix
    return Matrix4( (2 * zNear) / ( width - -width ), 0, (width + -width) / (width - -width), 0,
                    0, (2 * zNear) / (height - -height), (height + -height) / (height - -height), 0,
                    0, 0, -(zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
                    0, 0, -1, 0);
  }

  const Matrix4 Matrix4::LookAt(const Vector4& pos, const Vector4& target, Vector4& upDir)
  {
    // Compute Foward
    Vector4 forward = target - pos;
    forward.Normalize();

    // Compute up
    Vector4 up = upDir.Normalize();

    // Compute left vec
    Vector4 side = forward.Cross(up);
    side.Normalize();

    up = side.Cross(forward);
      
    //                X       Y       Z             T
    return Matrix4( side.x, up.x, -forward.x, -side.Dot(pos),
                    side.y, up.y, -forward.y, -up.Dot(pos),
                    side.z, up.z, -forward.z, forward.Dot(pos),
                          0,    0,         0,        1);
  }
}