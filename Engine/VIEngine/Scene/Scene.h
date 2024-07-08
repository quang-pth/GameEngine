#pragma once

#include"pch.h"
#include"ECS/ECSType.h"
#include"ECS/Coordinator.h"
#include"Core/Type/Actor.h"

namespace VIEngine {
	class Scene {
	public:
		Scene() = default;
		Scene(const Shared<ECS::Coordinator>& coordinator);
		~Scene();
		
		Actor CreateActor();
		void RemoveActor(ECS::EntityID id);

	protected:
		std::vector<ECS::EntityID> mEntityIDs;
		Shared<ECS::Coordinator> mCoordinator;
	}; // class Scene
} // namespace VIEngine