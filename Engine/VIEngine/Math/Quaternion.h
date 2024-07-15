#pragma once

#include"Vector.h"
#include"pch.h"

namespace Math {
	class VI_API Quaternion
	{
	public:
		float X;
		float Y;
		float Z;
		float W;

		Quaternion()
		{
			*this = Quaternion::Identity;
		}

		// This directly sets the quaternion components --
		// don't use for axis/angle
		explicit Quaternion(float inX, float inY, float inZ, float inW)
		{
			Set(inX, inY, inZ, inW);
		}

		// Construct the quaternion from an axis and angle
		// It is assumed that axis is already normalized,
		// and the angle is in radians
		explicit Quaternion(const Vector3& axis, float angle)
		{
			float scalar = Math::Sin(angle / 2.0f);
			X = axis.X * scalar;
			Y = axis.Y * scalar;
			Z = axis.Z * scalar;
			W = Math::Cos(angle / 2.0f);
		}

		// Directly set the internal components
		void Set(float inX, float inY, float inZ, float inW)
		{
			X = inX;
			Y = inY;
			Z = inZ;
			W = inW;
		}

		void Conjugate()
		{
			X *= -1.0f;
			Y *= -1.0f;
			Z *= -1.0f;
		}

		float LengthSquared() const
		{
			return (X * X + Y * Y + Z * Z + W * W);
		}

		float Length() const
		{
			return Math::Sqrt(LengthSquared());
		}

		void Normalize()
		{
			float length = Length();
			X /= length;
			Y /= length;
			Z /= length;
			W /= length;
		}

		// Normalize the provided quaternion
		static Quaternion Normalize(const Quaternion& q)
		{
			Quaternion retVal = q;
			retVal.Normalize();
			return retVal;
		}

		// Linear interpolation
		static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
		{
			Quaternion retVal;
			retVal.X = Math::Lerp(a.X, b.X, f);
			retVal.Y = Math::Lerp(a.Y, b.Y, f);
			retVal.Z = Math::Lerp(a.Z, b.Z, f);
			retVal.W = Math::Lerp(a.W, b.W, f);
			retVal.Normalize();
			return retVal;
		}

		static float Dot(const Quaternion& a, const Quaternion& b)
		{
			return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
		}

		// Spherical Linear Interpolation
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
		{
			float rawCosm = Quaternion::Dot(a, b);

			float cosom = -rawCosm;
			if (rawCosm >= 0.0f)
			{
				cosom = rawCosm;
			}

			float scale0, scale1;

			if (cosom < 0.9999f)
			{
				const float omega = Math::Acos(cosom);
				const float invSin = 1.f / Math::Sin(omega);
				scale0 = Math::Sin((1.f - f) * omega) * invSin;
				scale1 = Math::Sin(f * omega) * invSin;
			}
			else
			{
				// Use linear interpolation if the quaternions
				// are collinear
				scale0 = 1.0f - f;
				scale1 = f;
			}

			if (rawCosm < 0.0f)
			{
				scale1 = -scale1;
			}

			Quaternion retVal;
			retVal.X = scale0 * a.X + scale1 * b.X;
			retVal.Y = scale0 * a.Y + scale1 * b.Y;
			retVal.Z = scale0 * a.Z + scale1 * b.Z;
			retVal.W = scale0 * a.W + scale1 * b.W;
			retVal.Normalize();
			return retVal;
		}

		// Concatenate
		// Rotate by q FOLLOWED BY p
		static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
		{
			Quaternion retVal;

			// Vector component is:
			// ps * qv + qs * pv + pv x qv
			Vector3 qv(q.X, q.Y, q.Z);
			Vector3 pv(p.X, p.Y, p.Z);
			Vector3 newVec = p.W * qv + q.W * pv + Vector3::Cross(pv, qv);
			retVal.X = newVec.X;
			retVal.Y = newVec.Y;
			retVal.Z = newVec.Z;

			// Scalar component is:
			// ps * qs - pv . qv
			retVal.W = p.W * q.W - Vector3::Dot(pv, qv);

			return retVal;
		}

		static const Quaternion Identity;
	};
}