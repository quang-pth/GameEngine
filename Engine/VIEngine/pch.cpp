#include"pch.h"

namespace VIEngine {
	UUID GetUUID() {
		static std::random_device randomize;
		static std::mt19937_64 generator(randomize());
		static std::uniform_int_distribution<UUID> distribution;

		UUID uuid = INVALID_ID;
		do {
			uuid = distribution(generator);
		} while (uuid == INVALID_ID);

		return uuid;
	}
}