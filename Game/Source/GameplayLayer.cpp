#include"GameplayLayer.h"
#include<VIEngine/Base.h>

using namespace VIEngine;

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	MemoryManager memoryManager;
	Actor* actor = memoryManager.NewOnStack<Actor>("ActorManager");
	Object* obj = actor;

	LOG_TRACE(actor->RunTimeType.GetTypeName()); // Actor
	LOG_TRACE(actor->GetRunTimeTypeInfo().GetTypeName()); // Actor

	LOG_TRACE(obj->RunTimeType.GetTypeName()); // Object
	LOG_TRACE(obj->GetRunTimeTypeInfo().GetTypeName()); // Actor

	LOG_TRACE(actor->IsTypeOf(obj->RunTimeType)); // false
	LOG_TRACE(actor->IsDerivedFrom(obj->RunTimeType)); // true
	LOG_TRACE(actor->IsExactlyTypeOf(obj)); // true
	LOG_TRACE(actor->IsExactlyDerivedFrom(obj)); // true

	// Casting
	{
		int count = 100000;
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < count; i++) {
				auto obj = DownCast<Object>(actor);
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = endTime - startTime;
			LOG_INFO("RTTI takes {0} seconds", duration.count() / 1000.0f);
		}

		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < count; i++) {
				auto obj = dynamic_cast<Object*>(actor);
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = endTime - startTime;
			LOG_INFO("RTTI takes {0} seconds", duration.count() / 1000.0f);
		}
	}

	memoryManager.FreeOnStack(actor);
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(Time time) {
	
}

bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}

