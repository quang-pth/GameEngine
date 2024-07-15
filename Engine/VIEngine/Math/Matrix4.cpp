#include"Matrix4.h"

#include"Quaternion.h"

namespace Math {
	Matrix4 Matrix4::CreateFromQuaternion(const Quaternion& quaternion) {
		float Mat[4][4];

		Mat[0][0] = 1.0f - 2.0f * quaternion.Y * quaternion.Y - 2.0f * quaternion.Z * quaternion.Z;
		Mat[0][1] = 2.0f * quaternion.X * quaternion.Y + 2.0f * quaternion.W * quaternion.Z;
		Mat[0][2] = 2.0f * quaternion.X * quaternion.Z - 2.0f * quaternion.W * quaternion.Y;
		Mat[0][3] = 0.0f;

		Mat[1][0] = 2.0f * quaternion.X * quaternion.Y - 2.0f * quaternion.W * quaternion.Z;
		Mat[1][1] = 1.0f - 2.0f * quaternion.X * quaternion.X - 2.0f * quaternion.Z * quaternion.Z;
		Mat[1][2] = 2.0f * quaternion.Y * quaternion.Z + 2.0f * quaternion.W * quaternion.X;
		Mat[1][3] = 0.0f;

		Mat[2][0] = 2.0f * quaternion.X * quaternion.Z + 2.0f * quaternion.W * quaternion.Y;
		Mat[2][1] = 2.0f * quaternion.Y * quaternion.Z - 2.0f * quaternion.W * quaternion.X;
		Mat[2][2] = 1.0f - 2.0f * quaternion.X * quaternion.X - 2.0f * quaternion.Y * quaternion.Y;
		Mat[2][3] = 0.0f;

		Mat[3][0] = 0.0f;
		Mat[3][1] = 0.0f;
		Mat[3][2] = 0.0f;
		Mat[3][3] = 1.0f;

		return Matrix4(Mat);
		return Matrix4();
	}

	void Matrix4::Invert()
	{
		// Thanks slow math
		// This is a really janky way to unroll everything...
		float tmp[12];
		float src[16];
		float dst[16];
		float det;

		// Transpose matrix
		// row 1 to col 1
		src[0] = Mat[0][0];
		src[4] = Mat[0][1];
		src[8] = Mat[0][2];
		src[12] = Mat[0][3];

		// row 2 to col 2
		src[1] = Mat[1][0];
		src[5] = Mat[1][1];
		src[9] = Mat[1][2];
		src[13] = Mat[1][3];

		// row 3 to col 3
		src[2] = Mat[2][0];
		src[6] = Mat[2][1];
		src[10] = Mat[2][2];
		src[14] = Mat[2][3];

		// row 4 to col 4
		src[3] = Mat[3][0];
		src[7] = Mat[3][1];
		src[11] = Mat[3][2];
		src[15] = Mat[3][3];

		// Calculate cofactors
		tmp[0] = src[10] * src[15];
		tmp[1] = src[11] * src[14];
		tmp[2] = src[9] * src[15];
		tmp[3] = src[11] * src[13];
		tmp[4] = src[9] * src[14];
		tmp[5] = src[10] * src[13];
		tmp[6] = src[8] * src[15];
		tmp[7] = src[11] * src[12];
		tmp[8] = src[8] * src[14];
		tmp[9] = src[10] * src[12];
		tmp[10] = src[8] * src[13];
		tmp[11] = src[9] * src[12];

		dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
		dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
		dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
		dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
		dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
		dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
		dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
		dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
		dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
		dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
		dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
		dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
		dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
		dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
		dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
		dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

		tmp[0] = src[2] * src[7];
		tmp[1] = src[3] * src[6];
		tmp[2] = src[1] * src[7];
		tmp[3] = src[3] * src[5];
		tmp[4] = src[1] * src[6];
		tmp[5] = src[2] * src[5];
		tmp[6] = src[0] * src[7];
		tmp[7] = src[3] * src[4];
		tmp[8] = src[0] * src[6];
		tmp[9] = src[2] * src[4];
		tmp[10] = src[0] * src[5];
		tmp[11] = src[1] * src[4];

		dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
		dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
		dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
		dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
		dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
		dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
		dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
		dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
		dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
		dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
		dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
		dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
		dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
		dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
		dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
		dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

		// Calculate determinant
		det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

		// Inverse of matrix is divided by determinant
		det = 1 / det;
		for (int j = 0; j < 16; j++)
		{
			dst[j] *= det;
		}

		// Set it back
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Mat[i][j] = dst[i * 4 + j];
			}
		}
	}
}