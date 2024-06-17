#pragma once

namespace VIEngine {
	namespace ECS {
		enum class ESystemPriority {
			Low = 300,
			Medium = 200,
			High = 100
		};

		using EntityID = size_t;
		using ComponentID = size_t;
		using ComponentTypeID = size_t;
		using SystemID = size_t;
		using SystemTypeID = size_t;
	}
}