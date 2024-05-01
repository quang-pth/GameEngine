#include"ComponentManager.h"

namespace VIEngine {
	namespace ECS {
		ComponentManager::ComponentManager() {

		}

		ComponentManager::~ComponentManager() {
			for (auto& [componentTypeID, componentArray] : mComponentTypeMap) {
				VI_FREE_MEMORY(componentArray);
			}

			mComponentTypeMap.clear();
		}
	} // namespace ECS
} // namespace VIEngine