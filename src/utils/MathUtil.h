#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>

// Vector3D class
class Vector3D {
public:
    float x, y, z;

    Vector3D(float x = 0, float y = 0, float z = 0);

    void Normalize();
    float Dot(const Vector3D& v) const;
    Vector3D Cross(const Vector3D& v) const;
};

// Matrix4x4 class
class Matrix4x4 {
public:
    float m[4][4];

    Matrix4x4();

    void Translate(const Vector3D& v);
    void Scale(const Vector3D& v);
    void RotateZ(float angle);  // Example rotation around Z-axis
    // Other rotation functions can be added (RotateX, RotateY)
};

// Utility functions
Matrix4x4 MultiplyMatrix(const Matrix4x4& m1, const Matrix4x4& m2);
Vector3D Transform(const Vector3D& vec, const Matrix4x4& mat);
Matrix4x4 CreateProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

#endif // MATHUTIL_H
