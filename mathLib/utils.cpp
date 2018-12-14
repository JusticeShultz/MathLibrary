#include "utils.h"
#include <cmath>
#pragma region MathX
//MathX namespace indentifier.
namespace MathX
{
	#pragma region Vectors
	//Vector2:
	Vector2::Vector2(void) : X(0), Y(0) { }
	Vector2::Vector2(float xValue, float yValue) : X(xValue), Y(yValue) { }
	Vector2::Vector2(const Vector2 & v) : X(v.X), Y(v.Y) { }
	Vector2::Vector2(const Vector2 * v) : X(v->X), Y(v->Y) { }
	Vector2::~Vector2(void) { }

	void Vector2::Set(float xValue, float yValue) { X = xValue; Y = yValue; }
	float Vector2::Magnitude() const { return sqrt(((X * X) + (Y * Y))); }
	float Vector2::Length() const { return sqrt(X * X + Y * Y); }
	float Vector2::LengthSquared() const { return X * X + Y * Y; }
	float Vector2::Distance(const Vector2 & v) const { return sqrt(((X - v.X) * (X - v.X)) + ((Y - v.Y) * (Y - v.Y))); }
	float Vector2::DistanceSquared(const Vector2 & v) const { return ((X - v.X) * (X - v.X)) + ((Y - v.Y) * (Y - v.Y)); }
	float Vector2::Dot(const Vector2 & v) const { return X * v.X + Y * v.Y; }
	float Vector2::Cross(const Vector2 & v) const { return X * v.Y + Y * v.X; }

	Vector2 & Vector2::Normal() { Set(-Y, X); return *this; }
	Vector2 & Vector2::Normalize()
	{
		if (Length() != 0)
		{
			float length = LengthSquared();
			X /= length;
			Y /= length;
			return *this;
		}

		X = Y = 0;
		return *this;
	}

	//Vector 3:
	Vector3::Vector3(void) : X(0), Y(0), Z(0) { }
	Vector3::Vector3(float xValue, float yValue, float zValue) : X(xValue), Y(yValue), Z(zValue) { }
	Vector3::Vector3(const Vector3 & v) : X(v.X), Y(v.Y), Z(v.Z) { }
	Vector3::Vector3(const Vector3 * v) : X(v->X), Y(v->Y), Z(v->Z) { }
	Vector3::~Vector3(void) { }

	void Vector3::Set(float xValue, float yValue, float zValue) { X = xValue; Y = yValue; Z = zValue; }
	float Vector3::Magnitude() const { return sqrt(((X * X) + (Y * Y) + (Z * Z))); }
	float Vector3::Length() const { return sqrt(X * X + Y * Y + Z * Z); }
	float Vector3::LengthSquared() const { return X * X + Y * Y + Z * Z; }
	float Vector3::Distance(const Vector3 & v) const { return sqrt(((X - v.X) * (X - v.X)) + ((Y - v.Y) * (Y - v.Y)) + ((Z - v.Z) * (Z - v.Z))); }
	float Vector3::DistanceSquared(const Vector3 & v) const { return ((X - v.X) * (X - v.X)) + ((Y - v.Y) * (Y - v.Y)) + ((Z - v.Z) * (Z - v.Z)); }
	float Vector3::Dot(const Vector3 & v) const { return X * v.X + Y * v.Y + Z * v.Z; }
	float Vector3::Cross(const Vector3 & v) const { return X * v.Y + Y * v.X + Z * v.X; }

	Vector3 & Vector3::Normal() { Set(-Y, X, Z); return *this; }
	Vector3 & Vector3::Normalize()
	{
		if (Length() != 0)
		{
			float length = LengthSquared();
			X /= length;
			Y /= length;
			Z /= length;
			return *this;
		}

		X = Y = Z = 0;
		return *this;
	}

	//Vector 4:
	Vector4::Vector4(void) : X(0), Y(0), Z(0), W(0) { }
	Vector4::Vector4(float xValue, float yValue, float zValue, float wValue) : X(xValue), Y(yValue), Z(zValue), W(wValue) { }
	Vector4::Vector4(const Vector4 & v) : X(v.X), Y(v.Y), Z(v.Z), W(v.W) { }
	Vector4::Vector4(const Vector4 * v) : X(v->X), Y(v->Y), Z(v->Z), W(v->W) { }
	Vector4::~Vector4(void) { }

	void Vector4::Set(float xValue, float yValue, float zValue, float wValue) { X = xValue; Y = yValue; Z = zValue; W = wValue; }
	float Vector4::Magnitude() const { return sqrt(((X * X) + (Y * Y) + (Z * Z) + (W * W))); }
	float Vector4::Length() const { return sqrt(X * X + Y * Y + Z * Z + W * W); }
	float Vector4::LengthSquared() const { return X * X + Y * Y + Z * Z + W * W; }
	float Vector4::Distance(const Vector4 & v) const { return sqrt(((X - v.X) * (X - v.X)) + ((Y - v.Y) * (Y - v.Y)) + ((Z - v.Z) * (Z - v.Z)) + ((W - v.W) * (W - v.W))); }
	float Vector4::DistanceSquared(const Vector4 & v) const { return ((X - v.X) * (X - v.X)) + ((Y - v.Y) * (Y - v.Y)) + ((Z - v.Z) * (Z - v.Z)) + ((W - v.W) * (W - v.W)); }
	float Vector4::Dot(const Vector4 & v) const { return X * v.X + Y * v.Y + Z * v.Z + W * v.W; }
	float Vector4::Cross(const Vector4 & v) const { return X * v.Y + Y * v.X + Z * v.W + W * v.Z; }

	Vector4 & Vector4::Normal() { Set(-Y, X, Z, W); return *this; }
	Vector4 & Vector4::Normalize()
	{
		if (Length() != 0)
		{
			float length = LengthSquared();
			X /= length;
			Y /= length;
			Z /= length;
			W /= length;
			return *this;
		}

		X = Y = Z = W = 0;
		return *this;
	}
	#pragma endregion Definitions of vectors.

	#pragma region Matrices
	//Matrix 2:

	//Empty constructor(All default to 0).
	Matrix2::Matrix2()
	{
		for (int i = 0; i < 4; ++i) Row[i] = 0;
	}
	//Single fill constructor.
	Matrix2::Matrix2(int a)
	{
		for (int i = 0; i < 4; ++i) Row[i] = a;
	}
	//2 row constructor.
	Matrix2::Matrix2(int a, int b)
	{
		Row[0] = a, Row[1] = a,
		Row[2] = b, Row[3] = b;
	}
	//4 integral constructor.
	Matrix2::Matrix2(int a, int b, int c, int d)
	{
		Row[0] = a, Row[1] = b,
		Row[2] = c, Row[3] = d;
	}
	//Common deconstructor.
	Matrix2::~Matrix2() { delete Row; }
	
	//Matrix 3:

	//Empty constructor(All default to 0).
	Matrix3::Matrix3()
	{
		for (int i = 0; i < 9; ++i) Row[i] = 0;
	}
	//Single fill constructor.
	Matrix3::Matrix3(int a)
	{
		for (int i = 0; i < 9; ++i) Row[i] = a;
	}
	//3 row constructor.
	Matrix3::Matrix3(int a, int b, int c)
	{
		Row[0] = a, Row[1] = a, Row[2] = a,
		Row[3] = b, Row[4] = b, Row[5] = b,
		Row[6] = c, Row[7] = c, Row[8] = c;
	}
	//9 integral constructor.
	Matrix3::Matrix3(int a, int b, int c, int d, int e, int f, int g, int h, int i)
	{
		Row[0] = a, Row[1] = b, Row[2] = c,
		Row[3] = d, Row[4] = e, Row[5] = f,
		Row[6] = g, Row[7] = h, Row[8] = i;
	}
	//Common deconstructor.
	Matrix3::~Matrix3() { delete Row; }

	//Matrix 4:

	//Empty constructor(All default to 0).
	Matrix4::Matrix4()
	{
		for (int i = 0; i < 16; ++i) Row[i] = 0;
	}
	//Single fill constructor.
	Matrix4::Matrix4(int a)
	{
		for (int i = 0; i < 16; ++i) Row[i] = a;
	}
	//4 row constructor.
	Matrix4::Matrix4(int a, int b, int c, int d)
	{
		Row[0] = a, Row[1] = b, Row[2] = c, Row[3] = d,
		Row[4] = a, Row[5] = b, Row[6] = c, Row[7] = d,
		Row[8] = a, Row[9] = b, Row[10] = c, Row[11] = d,
		Row[12] = a, Row[13] = b, Row[14] = c, Row[15] = d;
	}
	//16 integral constructor.
	Matrix4::Matrix4(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p)
	{
		Row[0] = a, Row[1] = b, Row[2] = c, Row[3] = d,
		Row[4] = e, Row[5] = f, Row[6] = g, Row[7] = h,
		Row[8] = i, Row[9] = j, Row[10] = k, Row[11] = l,
		Row[12] = m, Row[13] = n, Row[14] = o, Row[15] = p;
	}
	//Common deconstructor.
	Matrix4::~Matrix4() { delete Row; }
	#pragma endregion Definitions for matrices.

	#pragma region Color
	//Color constructors:

	Color::Color() { R = 0, G = 0, B = 0, A = 0; }
	Color::Color(int v1) { R = v1, G = v1, B = v1, A = v1; }
	Color::Color(int v1, int v2, int v3, int v4) { R = v1, G = v2, B = v3, A = v4; }
	Color::~Color() { }
	#pragma endregion Definitions for color.

	#pragma region [DEPRECATED]
	///List of all deprecated functions - kept for possible future use or reference.
	///float Lerp(float start, float end, float amount) { return start + amount * (end - start); }
	///template <typename T> T Lerp(const T& a, const T& b, float t) { return a * (1 - t) + b * t; }
	#pragma endregion
}
#pragma endregion