#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API Time {
	public:
		Time() = default;
		Time(float deltaTime) : mDeltaTime(deltaTime), mTimeScale(1.0f) {

		}
		~Time() = default;

		VI_FORCE_INLINE float GetDeltaTime() const { return mDeltaTime; }
		VI_FORCE_INLINE void SetDeltaTime(float value) { mDeltaTime = value; }
		VI_FORCE_INLINE float GetTimeScale() const { return mTimeScale; }
		VI_FORCE_INLINE void SetTimeScale(float value) { mTimeScale = value; }

		VI_FORCE_INLINE friend Time& operator+=(Time& t1, const Time& t2) { t1.mDeltaTime += t2.GetDeltaTime(); return t1; }
		
		VI_FORCE_INLINE friend bool operator>=(const Time& t1, const Time& t2) { return t1.mDeltaTime >= t2.GetDeltaTime();}
		VI_FORCE_INLINE friend bool operator>(const Time& t1, const Time& t2) { return t1.mDeltaTime > t2.GetDeltaTime();}
		
		VI_FORCE_INLINE friend bool operator<=(const Time& t1, const Time& t2) { return t1.mDeltaTime <= t2.GetDeltaTime();}
		VI_FORCE_INLINE friend bool operator<(const Time& t1, const Time& t2) { return t1.mDeltaTime < t2.GetDeltaTime();}
		
		VI_FORCE_INLINE friend Time& operator-=(Time& t1, const Time& t2) { t1.mDeltaTime -= t2.GetDeltaTime(); return t1; }

	private:
		float mDeltaTime, mTimeScale;
	};
}