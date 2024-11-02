#include"Animation.h"
#include"AnimationResourceManager.h"
#include"Resource/Sprite.h"

namespace VIEngine {
	Animation* Animation::Create(const std::string& name) {
		return AnimationResourceManager::Get().NewAnimation(name);
	}

	Animation::Animation(const std::string& name) : mName(name), mSprites(), mNameHashID(GetHashID(name)), mCurrentFrameIdx(0), mIsLoop(true)
	{

	}

	Animation::~Animation() {

	}

	void Animation::NextFrame() {
		if (!mIsLoop && mCurrentFrameIdx == mSprites.size() - 1) {
			return;
		}

		mCurrentFrameIdx++;

		if (mCurrentFrameIdx >= mSprites.size()) {
			mCurrentFrameIdx -= mSprites.size();
		}
	}

	Sprite* Animation::AddSprite(const std::string& filepath)
	{
		mSprites.emplace_back(Sprite::Create(filepath));
		return mSprites.back();
	}

	void Animation::Release() {
		for (Sprite* sprite : mSprites) {
			sprite->Release();
		}
		mSprites.clear();
		//AnimationResourceManager::Get().FreeAnimation(this);
	}

	void Animation::RemoveSprite(const std::string& name)
	{
		auto iter = mSprites.begin();
		for (; iter != mSprites.end(); iter++) {
			if ((*iter)->GetName() == name) {
				break;
			}
		}

		if (iter != mSprites.end()) {
			(*iter)->Release();
			mSprites.erase(iter);
		}
	}
	
	void Animation::RemoveSprite(UUID nameHashID)
	{
		auto iter = mSprites.begin();
		for (; iter != mSprites.end(); iter++) {
			if (GetHashID((*iter)->GetName()) == nameHashID) {
				break;
			}
		}

		if (iter != mSprites.end()) {
			(*iter)->Release();
			mSprites.erase(iter);
		}
	}

	Sprite* Animation::GetSprite(uint16_t idx) const
	{
		if (idx >= mSprites.size()) {
			CORE_LOG_WARN("Animation {0} has {1} frames, but accessed at an invalid index {2}", mName, mSprites.size(), idx);
			return nullptr;
		}

		return mSprites[idx];
	}
}