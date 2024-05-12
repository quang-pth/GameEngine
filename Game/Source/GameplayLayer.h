#pragma once

#include<Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>
#include<Memory/MemoryAllocator.h>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}

	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");

		size_t size = 128 * 1024 * 1024;
		void* address = malloc(size);
		mAllocator = new VIEngine::StackAllocator(size, address);

		struct GameObject {
			size_t ID = 0;
			std::string Name = "GameObject";
		};
		
		std::vector<GameObject*> gameObjects;
		for (int i = 0; i < 10; i++) {
			void* memory = mAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i;
			go->Name = "GameObject: " + std::to_string(i);
			gameObjects.emplace_back(go);
		}		
		
		for (auto iter = gameObjects.rbegin(); iter != gameObjects.rend(); ++iter) {
			mAllocator->Free(*iter);
		}

		gameObjects.clear();

		for (int i = 0; i < 10; i++) {
			void* memory = mAllocator->Allocate(sizeof(GameObject), alignof(GameObject));
			GameObject* go = new (memory)GameObject();
			go->ID = i + 10;
			go->Name = "GameObject: " + std::to_string(i);
			gameObjects.emplace_back(go);
		}

		mAllocator->Clear();
		gameObjects.clear();
	}

	virtual void OnDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}

	virtual void OnUpdate(VIEngine::Time time) {
		LOG_TRACE("{0} deltaTime", time.GetDeltaTime());
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKey());
		return false;
	}
private:
	VIEngine::MemoryAllocator* mAllocator;
};


