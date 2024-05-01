#pragma once

#include"pch.h"
#include"ECS/Coordinator.h"

namespace VIEngine {
	class VI_API GameObject {
	public:
		GameObject();
		GameObject(ECS::Coordinator* coordinator);
		GameObject(ECS::EntityID id, ECS::Coordinator* coordinator);
		~GameObject();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			return mCoordinator->AddComponent<T>(mID, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() {
			return mCoordinator->GetComponent<T>(mID);
		}

		template<typename T>
		bool HasComponent() {
			return mCoordinator->HasComponent<T>(mID);
		}

		template<typename T>
		void RemoveComponent() {
			mCoordinator->RemoveComponent<T>(mID);
		}
	private:
		ECS::EntityID mID;
		ECS::Coordinator* mCoordinator;
	};
}