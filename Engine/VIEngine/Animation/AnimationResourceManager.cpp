#include"AnimationResourceManager.h"
#include"Core/GlobalMemory.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(AnimationResourceManager)

	AnimationResourceManager* AnimationResourceManager::sInstance = nullptr;

	AnimationResourceManager& AnimationResourceManager::Get() {
		if (sInstance == nullptr) {
			sInstance = GlobalMemoryUsage::Get().NewOnStack<AnimationResourceManager>(AnimationResourceManager::RunTimeType.GetTypeName());
		}

		return *sInstance;
	}

	AnimationResourceManager::AnimationResourceManager() : mAnimationMemoryManager("AnimationMemoryManager"), mAnimationMap() {

	}

	AnimationResourceManager::~AnimationResourceManager() {
		
	}

	Animation* AnimationResourceManager::GetAnimation(const std::string& name) {
		if (mAnimationMap.count(name)) {
			return mAnimationMap.at(name);
		}

		return nullptr;
	}

	Animation* AnimationResourceManager::NewAnimation(const std::string& name)
	{
 		if (mAnimationMap.count(name)) {
			CORE_LOG_WARN("Create duplicated animation {0}, using the already existed one!", name);
			return mAnimationMap.at(name);
		}

		Animation* animation = mAnimationMemoryManager.NewObject(name);
		mAnimationMap[name] = animation;
		return animation;
	}

	void AnimationResourceManager::FreeAnimation(Animation* animation)
	{
		VI_ASSERT(mAnimationMap.count(animation->GetName()) && "Failed to free non-existing animation");
		mAnimationMemoryManager.FreeObject(animation);
		mAnimationMap.erase(animation->GetName());
	}
}