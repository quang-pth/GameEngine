#pragma once

#include"pch.h"
#include"ECSType.h"

namespace VIEngine {
	namespace ECS {
		class VI_API IComponent {
		public:
			virtual ~IComponent() = default;
			virtual EntityID GetOwner() const = 0;
			virtual void SetOwner(EntityID id) = 0;
			virtual ComponentID GetID() const = 0;
			virtual void SetID(ComponentID id) = 0;
			virtual bool GetIsActive() const = 0;
			virtual void SetIsActive(bool value) = 0;
		protected:
			IComponent() = default;
		};

		template<typename T>
		class VI_API Component : public IComponent {
		public:
			VI_FORCE_INLINE static ComponentTypeID GetStaticTypeID() { return sStaticType; }
			VI_FORCE_INLINE static const char* GetStaticTypeString() { return typeid(T).name(); }
		public:
			Component() = default;
			Component(EntityID onwer, ComponentID id) : mOwner(owner), mID(id) {}

			VI_FORCE_INLINE EntityID GetOwner() const { return mOwner; }
			VI_FORCE_INLINE void SetOwner(EntityID id) { mOwner = id; }

			VI_FORCE_INLINE ComponentID GetID() const { return mID; }
			VI_FORCE_INLINE void SetID(ComponentID id) { mID = id; }

			VI_FORCE_INLINE bool GetIsActive() const { return mIsActive; }
			VI_FORCE_INLINE void SetIsActive(bool value) { mIsActive = value; }
		private:
			static ComponentTypeID sStaticType;
		private:
			EntityID mOwner = INVALID_ID;
			ComponentID mID = INVALID_ID;
			bool mIsActive = true;
		};

		template<typename T>
		ComponentTypeID Component<T>::sStaticType = GetTypeUUID<T>();
	} //namespace ECS
} // namespace VIEngine