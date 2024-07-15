#pragma once

#include"pch.h"
#include<memory>
#include"Utils.h"
#include"Vector.h"

namespace Math {
	class VI_API Matrix4
	{
	public:
		float Mat[4][4];

		Matrix4()
		{
			*this = Matrix4::Identity;
		}

		explicit Matrix4(float inMat[4][4])
		{
			memcpy(Mat, inMat, 16 * sizeof(float));
		}

		// Cast to a const float pointer
		const float* GetAsFloatPtr() const
		{
			return reinterpret_cast<const float*>(&Mat[0][0]);
		}

		// Matrix multiplication (a * b)
		friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
		{
			Matrix4 retVal;
			// row 0
			retVal.Mat[0][0] =
				a.Mat[0][0] * b.Mat[0][0] +
				a.Mat[0][1] * b.Mat[1][0] +
				a.Mat[0][2] * b.Mat[2][0] +
				a.Mat[0][3] * b.Mat[3][0];

			retVal.Mat[0][1] =
				a.Mat[0][0] * b.Mat[0][1] +
				a.Mat[0][1] * b.Mat[1][1] +
				a.Mat[0][2] * b.Mat[2][1] +
				a.Mat[0][3] * b.Mat[3][1];

			retVal.Mat[0][2] =
				a.Mat[0][0] * b.Mat[0][2] +
				a.Mat[0][1] * b.Mat[1][2] +
				a.Mat[0][2] * b.Mat[2][2] +
				a.Mat[0][3] * b.Mat[3][2];

			retVal.Mat[0][3] =
				a.Mat[0][0] * b.Mat[0][3] +
				a.Mat[0][1] * b.Mat[1][3] +
				a.Mat[0][2] * b.Mat[2][3] +
				a.Mat[0][3] * b.Mat[3][3];

			// row 1
			retVal.Mat[1][0] =
				a.Mat[1][0] * b.Mat[0][0] +
				a.Mat[1][1] * b.Mat[1][0] +
				a.Mat[1][2] * b.Mat[2][0] +
				a.Mat[1][3] * b.Mat[3][0];

			retVal.Mat[1][1] =
				a.Mat[1][0] * b.Mat[0][1] +
				a.Mat[1][1] * b.Mat[1][1] +
				a.Mat[1][2] * b.Mat[2][1] +
				a.Mat[1][3] * b.Mat[3][1];

			retVal.Mat[1][2] =
				a.Mat[1][0] * b.Mat[0][2] +
				a.Mat[1][1] * b.Mat[1][2] +
				a.Mat[1][2] * b.Mat[2][2] +
				a.Mat[1][3] * b.Mat[3][2];

			retVal.Mat[1][3] =
				a.Mat[1][0] * b.Mat[0][3] +
				a.Mat[1][1] * b.Mat[1][3] +
				a.Mat[1][2] * b.Mat[2][3] +
				a.Mat[1][3] * b.Mat[3][3];

			// row 2
			retVal.Mat[2][0] =
				a.Mat[2][0] * b.Mat[0][0] +
				a.Mat[2][1] * b.Mat[1][0] +
				a.Mat[2][2] * b.Mat[2][0] +
				a.Mat[2][3] * b.Mat[3][0];

			retVal.Mat[2][1] =
				a.Mat[2][0] * b.Mat[0][1] +
				a.Mat[2][1] * b.Mat[1][1] +
				a.Mat[2][2] * b.Mat[2][1] +
				a.Mat[2][3] * b.Mat[3][1];

			retVal.Mat[2][2] =
				a.Mat[2][0] * b.Mat[0][2] +
				a.Mat[2][1] * b.Mat[1][2] +
				a.Mat[2][2] * b.Mat[2][2] +
				a.Mat[2][3] * b.Mat[3][2];

			retVal.Mat[2][3] =
				a.Mat[2][0] * b.Mat[0][3] +
				a.Mat[2][1] * b.Mat[1][3] +
				a.Mat[2][2] * b.Mat[2][3] +
				a.Mat[2][3] * b.Mat[3][3];

			// row 3
			retVal.Mat[3][0] =
				a.Mat[3][0] * b.Mat[0][0] +
				a.Mat[3][1] * b.Mat[1][0] +
				a.Mat[3][2] * b.Mat[2][0] +
				a.Mat[3][3] * b.Mat[3][0];

			retVal.Mat[3][1] =
				a.Mat[3][0] * b.Mat[0][1] +
				a.Mat[3][1] * b.Mat[1][1] +
				a.Mat[3][2] * b.Mat[2][1] +
				a.Mat[3][3] * b.Mat[3][1];

			retVal.Mat[3][2] =
				a.Mat[3][0] * b.Mat[0][2] +
				a.Mat[3][1] * b.Mat[1][2] +
				a.Mat[3][2] * b.Mat[2][2] +
				a.Mat[3][3] * b.Mat[3][2];

			retVal.Mat[3][3] =
				a.Mat[3][0] * b.Mat[0][3] +
				a.Mat[3][1] * b.Mat[1][3] +
				a.Mat[3][2] * b.Mat[2][3] +
				a.Mat[3][3] * b.Mat[3][3];

			return retVal;
		}

		Matrix4& operator*=(const Matrix4& right)
		{
			*this = *this * right;
			return *this;
		}

		// Invert the matrix - super slow
		void Invert();

		// Get the translation component of the matrix
		Vector3 GetTranslation() const
		{
			return Vector3(Mat[3][0], Mat[3][1], Mat[3][2]);
		}

		// Get the X axis of the matrix (forward)
		Vector3 GetXAxis() const
		{
			return Vector3::Normalize(Vector3(Mat[0][0], Mat[0][1], Mat[0][2]));
		}

		// Get the Y axis of the matrix (left)
		Vector3 GetYAxis() const
		{
			return Vector3::Normalize(Vector3(Mat[1][0], Mat[1][1], Mat[1][2]));
		}

		// Get the Z axis of the matrix (up)
		Vector3 GetZAxis() const
		{
			return Vector3::Normalize(Vector3(Mat[2][0], Mat[2][1], Mat[2][2]));
		}

		// Extract the scale component from the matrix
		Vector3 GetScale() const
		{
			Vector3 retVal;
			retVal.X = Vector3(Mat[0][0], Mat[0][1], Mat[0][2]).Length();
			retVal.Y = Vector3(Mat[1][0], Mat[1][1], Mat[1][2]).Length();
			retVal.Z = Vector3(Mat[2][0], Mat[2][1], Mat[2][2]).Length();
			return retVal;
		}

		// Create a scale matrix with x, y, and z scales
		static Matrix4 CreateScale(float xScale, float yScale, float zScale)
		{
			float temp[4][4] =
			{
				{ xScale, 0.0f, 0.0f, 0.0f },
				{ 0.0f, yScale, 0.0f, 0.0f },
				{ 0.0f, 0.0f, zScale, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			};
			return Matrix4(temp);
		}

		static Matrix4 CreateScale(const Vector3& scaleVector)
		{
			return CreateScale(scaleVector.X, scaleVector.Y, scaleVector.Z);
		}

		// Create a scale matrix with a uniform factor
		static Matrix4 CreateScale(float scale)
		{
			return CreateScale(scale, scale, scale);
		}

		// Rotation about x-axis
		static Matrix4 CreateRotationX(float theta)
		{
			float temp[4][4] =
			{
				{ 1.0f, 0.0f, 0.0f , 0.0f },
				{ 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
				{ 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f },
			};
			return Matrix4(temp);
		}

		// Rotation about y-axis
		static Matrix4 CreateRotationY(float theta)
		{
			float temp[4][4] =
			{
				{ Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
				{ 0.0f, 1.0f, 0.0f, 0.0f },
				{ Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f },
			};
			return Matrix4(temp);
		}

		// Rotation about z-axis
		static Matrix4 CreateRotationZ(float theta)
		{
			float temp[4][4] =
			{
				{ Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
				{ -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f },
			};
			return Matrix4(temp);
		}

		// Create a rotation matrix from a quaternion
		static Matrix4 CreateFromQuaternion(const class Quaternion& q);

		static Matrix4 CreateTranslation(const Vector3& trans)
		{
			float temp[4][4] =
			{
				{ 1.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ trans.X, trans.Y, trans.Z, 1.0f }
			};
			return Matrix4(temp);
		}

		static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
		{
			Vector3 zaxis = Vector3::Normalize(target - eye);
			Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis));
			Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));
			Vector3 trans;
			trans.X = -Vector3::Dot(xaxis, eye);
			trans.Y = -Vector3::Dot(yaxis, eye);
			trans.Z = -Vector3::Dot(zaxis, eye);

			float temp[4][4] =
			{
				{ xaxis.X, yaxis.X, zaxis.X, 0.0f },
				{ xaxis.Y, yaxis.Y, zaxis.Y, 0.0f },
				{ xaxis.Z, yaxis.Z, zaxis.Z, 0.0f },
				{ trans.X, trans.Y, trans.Z, 1.0f }
			};
			return Matrix4(temp);
		}

		static Matrix4 CreateOrtho(float width, float height, float n, float f)
		{
			float temp[4][4] =
			{
				{ 2.0f / width, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 2.0f / height, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f / (f - n), 0.0f },
				{ 0.0f, 0.0f, n / (n - f), 1.0f }
			};
			return Matrix4(temp);
		}

		static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float n, float f)
		{
			float yScale = Math::Cot(fovY / 2.0f);
			float xScale = yScale * height / width;
			float temp[4][4] =
			{
				{ xScale, 0.0f, 0.0f, 0.0f },
				{ 0.0f, yScale, 0.0f, 0.0f },
				{ 0.0f, 0.0f, f / (f - n), 1.0f },
				{ 0.0f, 0.0f, -n * f / (f - n), 0.0f }
			};
			return Matrix4(temp);
		}

		// Create "Simple" View-Projection Matrix from Chapter 6
		static Matrix4 CreateSimpleViewProj(float width, float height)
		{
			float temp[4][4] =
			{
				{ 2.0f / width, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 2.0f / height, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 1.0f }
			};
			return Matrix4(temp);
		}

		static const Matrix4 Identity;
	};
}