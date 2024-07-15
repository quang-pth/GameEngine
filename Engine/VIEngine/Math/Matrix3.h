#pragma once

#include"pch.h"
#include<memory>
#include"Utils.h"
#include"Vector.h"

namespace Math {
	class VI_API Matrix3
	{
	public:
		float Mat[3][3];

		Matrix3()
		{
			*this = Matrix3::Identity;
		}

		explicit Matrix3(float inMat[3][3])
		{
			memcpy(Mat, inMat, 9 * sizeof(float));
		}

		// Cast to a const float pointer
		const float* GetAsFloatPtr() const
		{
			return reinterpret_cast<const float*>(&Mat[0][0]);
		}

		// Matrix multiplication
		friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
		{
			Matrix3 retVal;
			// row 0
			retVal.Mat[0][0] =
				left.Mat[0][0] * right.Mat[0][0] +
				left.Mat[0][1] * right.Mat[1][0] +
				left.Mat[0][2] * right.Mat[2][0];

			retVal.Mat[0][1] =
				left.Mat[0][0] * right.Mat[0][1] +
				left.Mat[0][1] * right.Mat[1][1] +
				left.Mat[0][2] * right.Mat[2][1];

			retVal.Mat[0][2] =
				left.Mat[0][0] * right.Mat[0][2] +
				left.Mat[0][1] * right.Mat[1][2] +
				left.Mat[0][2] * right.Mat[2][2];

			// row 1
			retVal.Mat[1][0] =
				left.Mat[1][0] * right.Mat[0][0] +
				left.Mat[1][1] * right.Mat[1][0] +
				left.Mat[1][2] * right.Mat[2][0];

			retVal.Mat[1][1] =
				left.Mat[1][0] * right.Mat[0][1] +
				left.Mat[1][1] * right.Mat[1][1] +
				left.Mat[1][2] * right.Mat[2][1];

			retVal.Mat[1][2] =
				left.Mat[1][0] * right.Mat[0][2] +
				left.Mat[1][1] * right.Mat[1][2] +
				left.Mat[1][2] * right.Mat[2][2];

			// row 2
			retVal.Mat[2][0] =
				left.Mat[2][0] * right.Mat[0][0] +
				left.Mat[2][1] * right.Mat[1][0] +
				left.Mat[2][2] * right.Mat[2][0];

			retVal.Mat[2][1] =
				left.Mat[2][0] * right.Mat[0][1] +
				left.Mat[2][1] * right.Mat[1][1] +
				left.Mat[2][2] * right.Mat[2][1];

			retVal.Mat[2][2] =
				left.Mat[2][0] * right.Mat[0][2] +
				left.Mat[2][1] * right.Mat[1][2] +
				left.Mat[2][2] * right.Mat[2][2];

			return retVal;
		}

		Matrix3& operator*=(const Matrix3& right)
		{
			*this = *this * right;
			return *this;
		}

		// Create a scale matrix with x and y scales
		static Matrix3 CreateScale(float xScale, float yScale)
		{
			float temp[3][3] =
			{
				{ xScale, 0.0f, 0.0f },
				{ 0.0f, yScale, 0.0f },
				{ 0.0f, 0.0f, 1.0f },
			};
			return Matrix3(temp);
		}

		static Matrix3 CreateScale(const Vector2& scaleVector)
		{
			return CreateScale(scaleVector.X, scaleVector.Y);
		}

		// Create a scale matrix with a uniform factor
		static Matrix3 CreateScale(float scale)
		{
			return CreateScale(scale, scale);
		}

		// Create a rotation matrix about the Z axis
		// theta is in radians
		static Matrix3 CreateRotation(float theta)
		{
			float temp[3][3] =
			{
				{ Math::Cos(theta), Math::Sin(theta), 0.0f },
				{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
				{ 0.0f, 0.0f, 1.0f },
			};
			return Matrix3(temp);
		}

		// Create a translation matrix (on the xy-plane)
		static Matrix3 CreateTranslation(const Vector2& trans)
		{
			float temp[3][3] =
			{
				{ 1.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ trans.X, trans.Y, 1.0f },
			};
			return Matrix3(temp);
		}

		static const Matrix3 Identity;
	};
}