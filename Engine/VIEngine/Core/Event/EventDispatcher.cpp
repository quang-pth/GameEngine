#include"EventDispatcher.h"

namespace VIEngine {
	std::unordered_map<const char*, std::vector<IEventAction*>> EventDispatcher::mActionMap;
}