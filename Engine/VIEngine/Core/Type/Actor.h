#pragma once

#include"pch.h"
#include"ECS/Coordinator.h"
#include"Object.h"

namespace VIEngine {
	class VI_API Actor : public Object {
	public:
		DECLARE_RTTI
	public:
		Actor() = default;
		Actor(Shared<ECS::Coordinator> coordinator);
		Actor(ECS::EntityID id, Shared<ECS::Coordinator> coordinator);
		~Actor();

		template<typename T, typename... Args>
		VI_FORCE_INLINE T& AddComponent(Args&&... args) { return mCoordinator->AddComponent<T>(mID, mCoordinator.get(), std::forward<Args>(args)...); }
		
		template<typename T>
		VI_FORCE_INLINE T& GetComponent() { return mCoordinator->GetComponent<T>(mID); }
		
		template<typename T>
		VI_FORCE_INLINE bool HasComponent() { return mCoordinator->HasComponent<T>(mID); }
		
		template<typename T>
		VI_FORCE_INLINE void RemoveComponent() { mCoordinator->RemoveComponent<T>(mID); }

		VI_FORCE_INLINE ECS::EntityID GetID() const { return mID; }

	private:
		ECS::EntityID mID;
		Shared<ECS::Coordinator> mCoordinator;
	};
}