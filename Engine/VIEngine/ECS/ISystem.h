#pragma once

#include"pch.h"
#include"Core/Time/Time.h"
#include"ECS/ECSType.h"

namespace VIEngine {
	namespace ECS {
		class VI_API ISystem {
		public:
			virtual ~ISystem() = default;
			virtual void OnInit() = 0;
			virtual void OnUpdate(Time) = 0;
			virtual void OnShutdown() = 0;
			virtual SystemID GetID() = 0;
			virtual void SetID(SystemID) = 0;
			virtual float GetUpdateInterval() const = 0;
			virtual void SetUpdateInterval(float value) = 0;
			virtual ESystemPriority GetPriority() const = 0;
			virtual void SetPriority(ESystemPriority value) = 0;
			virtual float GetLastUpdateTime() const = 0;
			virtual void SetLastUpdateTime(float) = 0;
			virtual void SetCoordinator(class Coordinator*) = 0;
		protected:
			ISystem() = default;
		};

		template<typename T>
		class VI_API System : public ISystem {
		public:
			static SystemTypeID GetStaticTypeID() { return sStaticType; }
		public:
			System() = default;
			System(SystemID id, ESystemPriority priority = ESystemPriority::Low) : mID(id), mPriority(priority) {}
			~System() = default;

			virtual void OnInit() override {}
			virtual void OnUpdate(Time) override {}
			virtual void OnShutdown() override {}

			VI_FORCE_INLINE virtual SystemID GetID() override { return mID; }
			VI_FORCE_INLINE virtual void SetID(SystemID id) override { mID = id; }

			VI_FORCE_INLINE float GetUpdateInterval() const { return mUpdateInterval; }
			VI_FORCE_INLINE void SetUpdateInterval(float value) { mUpdateInterval = value; }

			VI_FORCE_INLINE ESystemPriority GetPriority() const { return mPriority; }
			VI_FORCE_INLINE void SetPriority(ESystemPriority value) { mPriority = value; }

			VI_FORCE_INLINE virtual float GetLastUpdateTime() const override { return mLastUpdateTime; }
			VI_FORCE_INLINE virtual void SetLastUpdateTime(float value) override { mLastUpdateTime = value; }

			VI_FORCE_INLINE virtual void SetCoordinator(class Coordinator* coordinator) override { mCoordinator = coordinator; }
		private:
			static SystemTypeID sStaticType;
		private:
			SystemID mID = INVALID_ID;
			float mUpdateInterval = -1.0f;
			float mLastUpdateTime = 0.0f;
			ESystemPriority mPriority = ESystemPriority::Low;
			class Coordinator* mCoordinator;
		};

		template<typename T>
		SystemTypeID System<T>::sStaticType = GetTypeUUID<T>();
	} // namespace ECS
} // namespace VIEngine