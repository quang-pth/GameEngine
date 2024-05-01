#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API Time {
	public:
		Time() = default;
		Time(float deltaTime) : mDeltaTime(deltaTime), mTimeScale(1.0f) {}
		~Time() = default;

		VI_FORCE_INLINE float GetDeltaTime() const { return mDeltaTime * mTimeScale; }
		VI_FORCE_INLINE float GetTimeScale() const { return mTimeScale; }
		VI_FORCE_INLINE float SetTimeScale(float value) { mTimeScale = value; }

		VI_FORCE_INLINE friend float operator+=(Time& t1, const Time& t2) { t1.mDeltaTime += t2.GetDeltaTime(); return t1.mDeltaTime; }
		VI_FORCE_INLINE friend float operator-=(Time& t1, const Time& t2) { t1.mDeltaTime -= t2.GetDeltaTime(); return t1.mDeltaTime; }
		
		VI_FORCE_INLINE friend float operator>=(Time& t1, const Time& t2) { return t1.mDeltaTime >= t2.GetDeltaTime(); }
		VI_FORCE_INLINE friend float operator<=(Time& t1, const Time& t2) { return t1.mDeltaTime <= t2.GetDeltaTime(); }
		
		VI_FORCE_INLINE friend float operator>(Time& t1, const Time& t2) { return t1.mDeltaTime > t2.GetDeltaTime(); }
		VI_FORCE_INLINE friend float operator<(Time& t1, const Time& t2) { return t1.mDeltaTime < t2.GetDeltaTime(); }

	private:
		float mDeltaTime;
		float mTimeScale;
	};
}