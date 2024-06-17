#pragma once

#include"pch.h"
#include"ECSType.h"

namespace VIEngine {
	namespace ECS {
		class IComponent {
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
		class Component : public IComponent {
		public:
			VI_FORCE_INLINE static ComponentTypeID GetStaticTypeID() { return sStaticType; }
		public:
			Component() = default;
			Component(EntityID owner, ComponentID id) : mOwner(owner), mID(id) {}

			VI_FORCE_INLINE virtual EntityID GetOwner() const override { return mOwner; }
			VI_FORCE_INLINE virtual void SetOwner(EntityID id) override { mOwner = id; }
			VI_FORCE_INLINE virtual ComponentID GetID() const override { return mID; }
			VI_FORCE_INLINE virtual void SetID(ComponentID id) override { mID = id; }
			VI_FORCE_INLINE virtual bool GetIsActive() const override { return mIsActive; }
			VI_FORCE_INLINE virtual void SetIsActive(bool value) override { mIsActive = value; }
		private:
			static ComponentTypeID sStaticType;
		private:
			EntityID mOwner;
			ComponentID mID;
			bool mIsActive;
		};

		template<typename T>
		ComponentTypeID Component<T>::sStaticType = GetTypeUUID<T>();
	} // namespace ECS
} // namespace VIEngine