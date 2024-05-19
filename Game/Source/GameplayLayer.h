#pragma once

#include<Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>
#include<Memory/MemoryAllocator.h>

#include<chrono>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}

	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");

		size_t size = 128 * 1024 * 1024;

		struct GameObject {
			size_t ID = 0;
			std::string Name = "GameObject";
		};
		
		mLinearAllocator = new VIEngine::LinearAllocator(size, malloc(size));
		mStackAllocator = new VIEngine::StackAllocator(size, malloc(size));
		mPoolAllocator = new VIEngine::PoolAllocator(size, malloc(size), sizeof(GameObject), alignof(GameObject));
	
		int numOfObjects = 1000000;
		std::vector<GameObject*> objects;
		
		// NEW and DELETE operator
		auto startTime = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numOfObjects; i++) {
			GameObject* go = new GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		for (GameObject* object : objects) {
			VI_FREE_MEMORY(object);
		}

		objects.clear();

		for (int i = 0; i < numOfObjects; i++) {
			GameObject* go = new GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		for (GameObject* object : objects) {
			VI_FREE_MEMORY(object);
		}

		objects.clear();

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = endTime - startTime;
		CORE_LOG_INFO("Delete operator takes: {0} seconds", duration.count() / 1000.0f);

		// LINEAR ALLOCATOR
		startTime = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < numOfObjects; i++) {
			void* memory = mLinearAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		mLinearAllocator->Clear();
		objects.clear();

		for (int i = 0; i < numOfObjects; i++) {
			void* memory = mLinearAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		mLinearAllocator->Clear();
		objects.clear();

		endTime = std::chrono::high_resolution_clock::now();
		duration = endTime - startTime;
		CORE_LOG_INFO("LinearAllocator takes: {0} seconds", duration.count() / 1000.0f);

		// STACK ALLOCATOR
		startTime = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numOfObjects; i++) {
			void* memory = mStackAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		mStackAllocator->Clear();
		objects.clear();

		for (int i = 0; i < numOfObjects; i++) {
			void* memory = mStackAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		mStackAllocator->Clear();
		objects.clear();

		endTime = std::chrono::high_resolution_clock::now();
		duration = endTime - startTime;
		CORE_LOG_INFO("StackAllocator takes: {0} seconds", duration.count() / 1000.0f);

		// Pool ALLOCATOR
		startTime = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numOfObjects; i++) {
			void* memory = mPoolAllocator->AllocateChunk();
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		mPoolAllocator->Clear();
		objects.clear();

		for (int i = 0; i < numOfObjects; i++) {
			void* memory = mPoolAllocator->AllocateChunk();
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			objects.emplace_back(go);
		}

		mPoolAllocator->Clear();
		objects.clear();

		endTime = std::chrono::high_resolution_clock::now();
		duration = endTime - startTime;
		CORE_LOG_INFO("PoolAllocator takes: {0} seconds", duration.count() / 1000.0f);

		CORE_LOG_TRACE("DONE TESTING MEMROY ALLOCATOR");
	}

	virtual void OnDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}

	virtual void OnUpdate(VIEngine::Time time) {
		//LOG_TRACE("{0} deltaTime", time.GetDeltaTime());
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		//LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKey());
		return false;
	}
private:
	VIEngine::LinearAllocator* mLinearAllocator;
	VIEngine::StackAllocator* mStackAllocator;
	VIEngine::PoolAllocator* mPoolAllocator;
};


