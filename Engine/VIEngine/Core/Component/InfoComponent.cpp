#include"InfoComponent.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(InfoComponent)

	InfoComponent::InfoComponent(const std::string& name) : mName(name) {

	}

	InfoComponent::~InfoComponent() {

	}
}