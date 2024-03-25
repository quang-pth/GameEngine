#include"EventDispatcher.h"

namespace VIEngine {
	EventDispatcher::EventDispatcher() : mEventActionMap() {
	}

	EventDispatcher::~EventDispatcher() {
		for (auto& pair : mEventActionMap) {
			for (auto eventAction : pair.second) {
				VI_FREE_MEMORY(eventAction);
			}
			pair.second.clear();
		}
		mEventActionMap.clear();
	}
}