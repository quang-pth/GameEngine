#pragma once

#include"pch.h"
#include"ECSType.h"

namespace VIEngine {
	namespace ECS {
		class IComponent {
		public:
			virtual ~IComponent() = default;
			virtual void SetCoordinator(class Coordinator*) = 0;
			virtual EntityID GetOwnerID() const = 0;
			virtual void SetOwnerID(EntityID id) = 0;
			virtual ComponentID GetID() const = 0;
			virtual void SetID(ComponentID id) = 0;
			virtual bool GetIsActive() const = 0;
			virtual void SetIsActive(bool value) = 0;
		protected:
			IComponent() = default;
		};

		template<typename T, typename Owner>
		class Component : public IComponent {
		public:
			VI_FORCE_INLINE static ComponentTypeID GetStaticTypeID() { return sStaticType; }
		private:
			static ComponentTypeID sStaticType;
		public:
			Component() = default;
			Component(EntityID owner, ComponentID id) : mOwner(owner), mID(id) {}
			Owner GetOwner() const { return Owner(mOwner, mCoordinator); }
			virtual void SetCoordinator(class Coordinator* coordinator) override { mCoordinator = coordinator; };
			VI_FORCE_INLINE virtual EntityID GetOwnerID() const override { return mOwner; }
			VI_FORCE_INLINE virtual void SetOwnerID(EntityID id) override { mOwner = id; }
			VI_FORCE_INLINE virtual ComponentID GetID() const override { return mID; }
			VI_FORCE_INLINE virtual void SetID(ComponentID id) override { mID = id; }
			VI_FORCE_INLINE virtual bool GetIsActive() const override { return mIsActive; }
			VI_FORCE_INLINE virtual void SetIsActive(bool value) override { mIsActive = value; }
		protected:
			EntityID mOwner;
			ComponentID mID;
			bool mIsActive;
			class Coordinator* mCoordinator;
		};

		template<typename T, typename Owner>
		ComponentTypeID Component<T, Owner>::sStaticType = GetTypeUUID<T>();
	} // namespace ECS
} // namespace VIEngine