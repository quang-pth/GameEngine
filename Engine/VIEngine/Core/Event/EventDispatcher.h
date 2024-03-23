#pragma once

#include"EventAction.h"

namespace VIEngine {
	class VI_API EventDispatcher {
	public:
		template<typename T>
		static void AddEventListener(const EventCallback<T>& callback) {
			VI_STATIC_ASSERT(std::is_base_of<IEvent, T>::value && "Add unknow event listener");
			const char* eventID = typeid(T).name();
			IEventAction* eventAction = new EventAction<T>(callback);
			mActionMap[eventID].emplace_back(eventAction);
		}

		template<typename T>
		static void DispatchEventListeners(const T& eventObject) {
			VI_STATIC_ASSERT(std::is_base_of<IEvent, T>::value && "Add unknow event listener");
			const char* eventID = typeid(T).name();
			VI_ASSERT(mActionMap.find(eventID) != mActionMap.end() && "Dispatch unregistered event listener");
			for (IEventAction* eventAction : mActionMap.at(eventID)) {
				if (eventAction->Execute(&eventObject)) {
					break;
				}
			}
		}
	private:
		EventDispatcher() = default;
		~EventDispatcher() = default;
	private:
		static std::unordered_map<const char*, std::vector<IEventAction*>> mActionMap;
	};
}