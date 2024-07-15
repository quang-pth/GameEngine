#pragma once

#include<cmath>
#include<memory>
#include<limits>
#include"Utils.h"
#include"pch.h"

namespace Math {
	class VI_API Vector2
	{
	public:
		float X;
		float Y;

		Vector2()
			: X(0.0f)
			, Y(0.0f)
		{}

		explicit Vector2(float inX, float inY)
			: X(inX)
			, Y(inY)
		{}

		// Set both components in one line
		void Set(float inX, float inY)
		{
			X = inX;
			Y = inY;
		}

		const float* GetAsFloatPtr() const
		{
			return reinterpret_cast<const float*>(&X);
		}

		// Vector addition (a + b)
		friend Vector2 operator+(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.X + b.X, a.Y + b.Y);
		}

		// Vector subtraction (a - b)
		friend Vector2 operator-(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.X - b.X, a.Y - b.Y);
		}

		// Component-wise multiplication
		// (a.x * b.x, ...)
		friend Vector2 operator*(const Vector2& a, const Vector2& b)
		{
			return Vector2(a.X * b.X, a.Y * b.Y);
		}

		// Scalar multiplication
		friend Vector2 operator*(const Vector2& vec, float scalar)
		{
			return Vector2(vec.X * scalar, vec.Y * scalar);
		}

		// Scalar multiplication
		friend Vector2 operator*(float scalar, const Vector2& vec)
		{
			return Vector2(vec.X * scalar, vec.Y * scalar);
		}

		// Scalar *=
		Vector2& operator*=(float scalar)
		{
			X *= scalar;
			Y *= scalar;
			return *this;
		}

		// Vector +=
		Vector2& operator+=(const Vector2& right)
		{
			X += right.X;
			Y += right.Y;
			return *this;
		}

		// Vector -=
		Vector2& operator-=(const Vector2& right)
		{
			X -= right.X;
			Y -= right.Y;
			return *this;
		}

		// Length squared of vector
		float LengthSquared() const
		{
			return (X * X + Y * Y);
		}

		// Length of vector
		float Length() const
		{
			return (Math::Sqrt(LengthSquared()));
		}

		// Normalize this vector
		void Normalize()
		{
			float length = Length();
			X /= length;
			Y /= length;
		}

		// Normalize the provided vector
		static Vector2 Normalize(const Vector2& vec)
		{
			Vector2 temp = vec;
			temp.Normalize();
			return temp;
		}

		// Dot product between two vectors (a dot b)
		static float Dot(const Vector2& a, const Vector2& b)
		{
			return (a.X * b.X + a.Y * b.Y);
		}

		// Lerp from A to B by f
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
		{
			return Vector2(a + f * (b - a));
		}

		// Reflect V about (normalized) N
		static Vector2 Reflect(const Vector2& v, const Vector2& n)
		{
			return v - 2.0f * Vector2::Dot(v, n) * n;
		}

		// Transform vector by matrix
		static Vector2 Transform(const Vector2& vec, const class Matrix3& Mat, float w = 1.0f);

		static const Vector2 Zero;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 NegUnitX;
		static const Vector2 NegUnitY;
	};

	// 3D Vector
	class VI_API Vector3
	{
	public:
		float X;
		float Y;
		float Z;

		Vector3()
			: X(0.0f)
			, Y(0.0f)
			, Z(0.0f)
		{}

		explicit Vector3(float inX, float inY, float inZ)
			: X(inX)
			, Y(inY)
			, Z(inZ)
		{}

		// Cast to a const float pointer
		const float* GetAsFloatPtr() const
		{
			return reinterpret_cast<const float*>(&X);
		}

		// Set all three components in one line
		void Set(float inX, float inY, float inZ)
		{
			X = inX;
			Y = inY;
			Z = inZ;
		}

		// Vector addition (a + b)
		friend Vector3 operator+(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
		}

		// Vector subtraction (a - b)
		friend Vector3 operator-(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
		}

		// Component-wise multiplication
		friend Vector3 operator*(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.X * right.X, left.Y * right.Y, left.Z * right.Z);
		}

		// Scalar multiplication
		friend Vector3 operator*(const Vector3& vec, float scalar)
		{
			return Vector3(vec.X * scalar, vec.Y * scalar, vec.Z * scalar);
		}

		// Scalar multiplication
		friend Vector3 operator*(float scalar, const Vector3& vec)
		{
			return Vector3(vec.X * scalar, vec.Y * scalar, vec.Z * scalar);
		}

		// Scalar *=
		Vector3& operator*=(float scalar)
		{
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
			return *this;
		}

		// Vector +=
		Vector3& operator+=(const Vector3& right)
		{
			X += right.X;
			Y += right.Y;
			Z += right.Z;
			return *this;
		}

		// Vector -=
		Vector3& operator-=(const Vector3& right)
		{
			X -= right.X;
			Y -= right.Y;
			Z -= right.Z;
			return *this;
		}

		// Length squared of vector
		float LengthSquared() const
		{
			return (X * X + Y * Y + Z * Z);
		}

		// Length of vector
		float Length() const
		{
			return (Math::Sqrt(LengthSquared()));
		}

		// Normalize this vector
		void Normalize()
		{
			float length = Length();
			X /= length;
			Y /= length;
			Z /= length;
		}

		// Normalize the provided vector
		static Vector3 Normalize(const Vector3& vec)
		{
			Vector3 temp = vec;
			temp.Normalize();
			return temp;
		}

		// Dot product between two vectors (a dot b)
		static float Dot(const Vector3& a, const Vector3& b)
		{
			return (a.X * b.X + a.Y * b.Y + a.Z * b.Z);
		}

		// Cross product between two vectors (a cross b)
		static Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			Vector3 temp;
			temp.X = a.Y * b.Z - a.Z * b.Y;
			temp.Y = a.Z * b.X - a.X * b.Z;
			temp.Z = a.X * b.Y - a.Y * b.X;
			return temp;
		}

		// Lerp from A to B by f
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
		{
			return Vector3(a + f * (b - a));
		}

		// Reflect V about (normalized) N
		static Vector3 Reflect(const Vector3& v, const Vector3& n)
		{
			return v - 2.0f * Vector3::Dot(v, n) * n;
		}

		static Vector3 Transform(const Vector3& vec, const class Matrix4& Mat, float w = 1.0f);
		// This will transform the vector and renormalize the w component
		static Vector3 TransformWithPerspDiv(const Vector3& vec, const class Matrix4& Mat, float w = 1.0f);

		// Transform a Vector3 by a quaternion
		static Vector3 Transform(const Vector3& v, const class Quaternion& q);

		static const Vector3 Zero;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 NegUnitX;
		static const Vector3 NegUnitY;
		static const Vector3 NegUnitZ;
		static const Vector3 Infinity;
		static const Vector3 NegInfinity;
	};
}