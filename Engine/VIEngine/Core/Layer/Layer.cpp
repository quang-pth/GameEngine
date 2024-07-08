#include"Layer.h"

namespace VIEngine {
	Layer::Layer() : mID(GetUUID()) {

	}

	Layer::Layer(Shared<Scene> scene) : mID(GetUUID()), mScene(scene) {

	}
}