#include"Vector.h"

#include"Matrix3.h"
#include"Matrix4.h"
#include"Quaternion.h"

namespace Math {
	const Vector2 Vector2::Zero(0.0f, 0.0f);
	const Vector2 Vector2::UnitX(1.0f, 0.0f);
	const Vector2 Vector2::UnitY(0.0f, 1.0f);
	const Vector2 Vector2::NegUnitX(-1.0f, 0.0f);
	const Vector2 Vector2::NegUnitY(0.0f, -1.0f);

	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.f);
	const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::NegUnitX(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::NegUnitY(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::NegUnitZ(0.0f, 0.0f, -1.0f);
	const Vector3 Vector3::Infinity(Math::Infinity, Math::Infinity, Math::Infinity);
	const Vector3 Vector3::NegInfinity(Math::NegInfinity, Math::NegInfinity, Math::NegInfinity);

	Vector2 Vector2::Transform(const Vector2& vec, const Matrix3& Mat, float w /*= 1.0f*/)
	{
		Vector2 retVal;
		retVal.X = vec.X * Mat.Mat[0][0] + vec.Y * Mat.Mat[1][0] + w * Mat.Mat[2][0];
		retVal.Y = vec.X * Mat.Mat[0][1] + vec.Y * Mat.Mat[1][1] + w * Mat.Mat[2][1];
		//ignore w since we aren't returning a new value for it...
		return retVal;
	}

	Vector3 Vector3::Transform(const Vector3& vec, const Matrix4& Mat, float w /*= 1.0f*/)
	{
		Vector3 retVal;
		retVal.X = vec.X * Mat.Mat[0][0] + vec.Y * Mat.Mat[1][0] +
			vec.Z * Mat.Mat[2][0] + w * Mat.Mat[3][0];
		retVal.Y = vec.X * Mat.Mat[0][1] + vec.Y * Mat.Mat[1][1] +
			vec.Z * Mat.Mat[2][1] + w * Mat.Mat[3][1];
		retVal.Z = vec.X * Mat.Mat[0][2] + vec.Y * Mat.Mat[1][2] +
			vec.Z * Mat.Mat[2][2] + w * Mat.Mat[3][2];
		//ignore w since we aren't returning a new value for it...
		return retVal;
	}

	// This will transform the vector and renormalize the w component
	Vector3 Vector3::TransformWithPerspDiv(const Vector3& vec, const Matrix4& Mat, float w /*= 1.0f*/)
	{
		Vector3 retVal;
		retVal.X = vec.X * Mat.Mat[0][0] + vec.Y * Mat.Mat[1][0] +
			vec.Z * Mat.Mat[2][0] + w * Mat.Mat[3][0];
		retVal.Y = vec.X * Mat.Mat[0][1] + vec.Y * Mat.Mat[1][1] +
			vec.Z * Mat.Mat[2][1] + w * Mat.Mat[3][1];
		retVal.Z = vec.X * Mat.Mat[0][2] + vec.Y * Mat.Mat[1][2] +
			vec.Z * Mat.Mat[2][2] + w * Mat.Mat[3][2];
		float transformedW = vec.X * Mat.Mat[0][3] + vec.Y * Mat.Mat[1][3] +
			vec.Z * Mat.Mat[2][3] + w * Mat.Mat[3][3];
		if (!Math::NearZero(Math::Abs(transformedW)))
		{
			transformedW = 1.0f / transformedW;
			retVal *= transformedW;
		}
		return retVal;
	}

	// Transform a Vector3 by a quaternion
	Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
	{
		// v + 2.0*cross(q.Xyz, cross(q.Xyz,v) + q.w*v);
		Vector3 qv(q.X, q.Y, q.Z);
		Vector3 retVal = v;
		retVal += 2.0f * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.W * v);
		return retVal;
	}
}