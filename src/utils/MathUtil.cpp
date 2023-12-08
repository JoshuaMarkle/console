#include "MathUtil.h"

const float PI = 3.1415926;

// Vector3D Constructor
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

// Vector Normalization
void Vector3D::Normalize() {
    float length = sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}

// Dot Product
float Vector3D::Dot(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Cross Product
Vector3D Vector3D::Cross(const Vector3D& v) const {
    return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

// Matrix4x4 Constructor - Initialize to Identity Matrix
Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Matrix Translation
void Matrix4x4::Translate(const Vector3D& v) {
    m[3][0] = v.x;
    m[3][1] = v.y;
    m[3][2] = v.z;
}

// Matrix Scaling
void Matrix4x4::Scale(const Vector3D& v) {
    m[0][0] = v.x;
    m[1][1] = v.y;
    m[2][2] = v.z;
}

// Matrix Rotation X
void Matrix4x4::RotateX(float angle) {
	float rad = angle * PI / 180.0f;
	float cosine = cos(rad), sine = sin(rad);
	Matrix4x4 rotation;
	rotation.m[1][1] = cosine;
	rotation.m[1][2] = -sine;
	rotation.m[2][1] = sine;
	rotation.m[2][2] = cosine;
	*this = MultiplyMatrix(*this, rotation);
}

// Matrix Rotation Y
void Matrix4x4::RotateY(float angle) {
	float rad = angle * PI / 180.0f;
	float cosine = cos(rad), sine = sin(rad);
	Matrix4x4 rotation;
	rotation.m[0][0] = cosine;
	rotation.m[0][2] = sine;
	rotation.m[2][0] = -sine;
	rotation.m[2][2] = cosine;
	*this = MultiplyMatrix(*this, rotation);
}

// Matrix Rotation Z
void Matrix4x4::RotateZ(float angle) {
	float rad = angle * PI / 180.0f;
	float cosine = cos(rad), sine = sin(rad);
	Matrix4x4 rotation;
	rotation.m[0][0] = cosine;
	rotation.m[0][1] = -sine;
	rotation.m[1][0] = sine;
	rotation.m[1][1] = cosine;
	*this = MultiplyMatrix(*this, rotation);
}

// Multiply two matrices
Matrix4x4 MultiplyMatrix(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return result;
}

// Transform a vector by a matrix
Vector3D Transform(const Vector3D& vec, const Matrix4x4& mat) {
    return Vector3D(
        vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0],
        vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1],
        vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2]
    );
}

// Create a projection matrix
Matrix4x4 CreateProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
    Matrix4x4 projMatrix;
    float yScale = 1.0f / tan(fov / 2.0f);
    float xScale = yScale / aspectRatio;
    float frustumLength = farPlane - nearPlane;

    projMatrix.m[0][0] = xScale;
    projMatrix.m[1][1] = yScale;
    projMatrix.m[2][2] = -((farPlane + nearPlane) / frustumLength);
    projMatrix.m[2][3] = -1;
    projMatrix.m[3][2] = -((2 * nearPlane * farPlane) / frustumLength);
    projMatrix.m[3][3] = 0;

    return projMatrix;
}
