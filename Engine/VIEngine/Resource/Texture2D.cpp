#include"Texture2D.h"

#include"ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(Texture2D, Object::RunTimeType)

	Texture2D* Texture2D::Create(const std::string& filepath, bool alpha) {
		return ResourceManager::Get().NewTexture2D(filepath, alpha);
	}
}