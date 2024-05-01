#pragma once

#include"IComponent.h"
#include"Memory/MemoryChunkManager.h"

namespace VIEngine {
	namespace ECS {
		class VI_API ComponentManager {

			class VI_API IComponentArray {
			public:
				virtual ~IComponentArray() = default;
				virtual bool HasComponent(EntityID) = 0;
				virtual void RemoveComponent(EntityID) = 0;
			};

		public:
			template<typename T>
			class VI_API ComponentArray : public MemoryChunkManager<T, MAX_OBJECTS_PER_CHUNK>, public IComponentArray {
			public:
				ComponentArray() = default;

				ComponentArray(const char* allocatorTag) : MemoryChunkManager(allocatorTag) {
				}

				~ComponentArray() {
				}

				template<typename... Args>
				T& AddComponent(EntityID entityID, Args&&... args) {
					VI_BASE_CLASS_STATIC_ASSERT(IComponent, T, "Add invalid component type");
					void* address = Allocate();
					
					IComponent* component = new (address)T(std::forward<Args>(args)...);
					component->SetOwner(entityID);
					component->SetID(GetUUID());

					mComponentsMap[entityID] = static_cast<T*>(component);

					return *mComponentsMap[entityID];
				}

				T& GetComponent(EntityID entityID) {
					VI_BASE_CLASS_STATIC_ASSERT(IComponent, T, "Get invalid component type");
					VI_ASSERT(mComponentsMap.count(entityID) && "Get non-existing component of entity");
					
					return *static_cast<T*>(mComponentsMap.at(entityID));
				}

				virtual bool HasComponent(EntityID entityID) override {
					VI_BASE_CLASS_STATIC_ASSERT(IComponent, T, "Get invalid component type");
					return mComponentsMap.count(entityID) != 0;
				}

				virtual void RemoveComponent(EntityID entityID) override {
					VI_BASE_CLASS_STATIC_ASSERT(IComponent, T, "Get invalid component type");
					T* component = mComponentsMap.at(entityID);
					Free(component);
					mComponentsMap.erase(entityID);
				}
			private:
				std::unordered_map<EntityID, T*> mComponentsMap;
			};

			using ComponentTypeMap = std::unordered_map<ComponentTypeID, IComponentArray*>;

		public:
			ComponentManager();
			~ComponentManager();

			template<typename T>
			ComponentArray<T>& GetComponentArray() {
				VI_BASE_CLASS_STATIC_ASSERT(IComponent, T, "Get invalid component array");
				ComponentTypeID componentTypeID = T::GetStaticTypeID();
				VI_ASSERT(mComponentTypeMap.count(componentTypeID) && "Not registered component array");
				return *static_cast<ComponentArray<T>*>(mComponentTypeMap.at(componentTypeID));
			}

			template<typename T, typename... Args>
			T& AddComponent(EntityID entityID, Args&&... args) {
				ComponentTypeID componentTypeID = T::GetStaticTypeID();

				if (!mComponentTypeMap.count(componentTypeID)) {
					IComponentArray* componentArray = new ComponentArray<T>(GetAllocatorTag());
					mComponentTypeMap[componentTypeID] = componentArray;
				}

				ComponentArray<T>* componentArray = static_cast<ComponentArray<T>*>(mComponentTypeMap.at(componentTypeID));
				return componentArray->AddComponent(entityID, std::forward<Args>(args)...);
			}

			template<typename T>
			T& GetComponent(EntityID entityID) {
				ComponentTypeID componentTypeID = T::GetStaticTypeID();
				ComponentArray<T>* componentArray = static_cast<ComponentArray<T>*>(mComponentTypeMap.at(componentTypeID));
				return componentArray->GetComponent(entityID);
			}

			template<typename T>
			bool HasComponent(EntityID entityID) {
				ComponentTypeID componentTypeID = T::GetStaticTypeID();

				if (!mComponentTypeMap.count(componentTypeID)) {
					CORE_LOG_WARN("Checking non-existing component type {0}", T::GetStaticTypeString());
					return false;
				}

				ComponentArray<T>* componentArray = static_cast<ComponentArray<T>*>(mComponentTypeMap.at(componentTypeID));
				return componentArray->HasComponent(entityID);
			}
			
			template<typename T>
			void RemoveComponent(EntityID entityID) {
				if (!HasComponent<T>(entityID)) return;

				ComponentTypeID componentTypeID = T::GetStaticTypeID();
				ComponentArray<T>* componentArray = static_cast<ComponentArray<T>*>(mComponentTypeMap.at(componentTypeID));
				componentArray->RemoveComponent(entityID);
			}

			void RemoveRelatedComponents(EntityID entityID) {
				for (auto& [_, componentArray] : mComponentTypeMap) {
					if (!componentArray->HasComponent(entityID)) continue;
					componentArray->RemoveComponent(entityID);
				}

				mComponentTypeMap.erase(entityID);
			}
		private:
			static const char* GetAllocatorTag() { return "ComponentManager"; }

		private:
			ComponentTypeMap mComponentTypeMap;
		};

	} // namespace ECS
} // namespace VIEngine