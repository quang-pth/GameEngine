#include"ResourceManager.h"
#include"Core/GlobalMemory.h"
#include"Renderer/OpenGL/OpenGLResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>

namespace VIEngine {
	ResourceManager* ResourceManager::sInstance = nullptr;

	ResourceManager& ResourceManager::Get()
	{
		return *sInstance;
	}

	void ResourceManager::OnInit(ERendererSpec rendererSpec)
	{
		switch (rendererSpec)
		{
		case VIEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::Get().NewOnStack<OpenGLResourceManager>(OpenGLResourceManager::RunTimeType.GetTypeName());
			break;
		case VIEngine::ERendererSpec::DirectX:
			VI_ASSERT("Currently not supported for Direct X");
			break;
		default:
			VI_ASSERT("Unkown renderer spec!");
			break;
		}
	}

	void ResourceManager::OnShutdown()
	{
		sInstance->OnReset();
	}

	ResourceManager::ResourceManager() : mSpriteMemoryManager("SpriteMemoryManager") {

	}

	void ResourceManager::OnReset() {
		mSpriteMemoryManager.Reset();
	}

	Sprite* ResourceManager::NewSprite(const std::string& filepath) {
		return mSpriteMemoryManager.NewObject(filepath);
	}

	void ResourceManager::FreeSprite(Sprite* sprite) {
		mSpriteMemoryManager.FreeObject(sprite);
	}
}