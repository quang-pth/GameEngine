#pragma once

#include"Memory/MemoryChunkManager.h"
#include"Animation.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	class VI_API AnimationResourceManager {
	public:
		DECLARE_RTTI
	public:
		static AnimationResourceManager& Get();
	private:
		static AnimationResourceManager* sInstance;
	public:
		AnimationResourceManager();
		~AnimationResourceManager();
		Animation* GetAnimation(const std::string& name);
		Animation* NewAnimation(const std::string& name);
		void FreeAnimation(Animation* animation);
	private:
		MemoryChunkManager<Animation, 100> mAnimationMemoryManager;
		std::unordered_map<std::string, Animation*> mAnimationMap;
	};
}