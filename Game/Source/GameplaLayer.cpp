#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<chrono>

using namespace VIEngine;

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	MemoryManager memoryManager;
	GameObject* go = memoryManager.NewOnStack<GameObject>("MemoryManager");
	Object* obj = go;

	//LOG_TRACE(go->RunTimeType.GetTypeName()); // VIEngine::GameObject
	//LOG_TRACE(go->GetRTTI().GetTypeName()); // VIEngine::GameObject

	int count = 100000;
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < count; i++) {
			auto actor = DownCast<Actor>(obj);
			if (actor) {
				auto typeName = actor->GetRTTI().GetTypeName();
			}
		}
		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = endTime - startTime;
		CORE_LOG_INFO("RTTI takes {0} seconds", duration.count() / 1000.0f);
	}
	
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < count; i++) {
			auto actor = dynamic_cast<Actor*>(obj);
			if (actor) {
				auto typeName = typeid(Actor).name();
			}
		}
		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = endTime - startTime;
		CORE_LOG_INFO("RTTI takes {0} seconds", duration.count() / 1000.0f);
	}

	//LOG_TRACE(obj->RunTimeType.GetTypeName()); // VIEngine::Object
	//LOG_TRACE(obj->GetRTTI().GetTypeName()); // VIEngine::GameObject

	//LOG_TRACE(go->IsTypeOf(obj->RunTimeType)); // true
	//LOG_TRACE(go->IsDerivedFrom(obj->RunTimeType)); // true
	//LOG_TRACE(go->IsExactlyTypeOf(obj)); // true
	//LOG_TRACE(go->IsExactlyDerivedFrom(obj)); // true

	
	//Actor* actor = DynamicCast<Actor>(go);
	/*if (!actor) {
		LOG_WARN("Casting failed");
	}*/
	memoryManager.ClearOnStack();
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(Time time) {
	//LOG_TRACE("GameplayLayer is detached");
}

bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}
