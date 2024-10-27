#include"Animation.h"
#include"AnimationResourceManager.h"

namespace VIEngine {
	Animation* Animation::Create(const std::string& name) {
		return AnimationResourceManager::Get().NewAnimation(name);
	}

	Animation::Animation(const std::string& name) : mName(name), mTextures(), mNameHashID(GetHashID(name)), mCurrentFrameIdx(0), mIsLoop(true)
	{

	}

	Animation::~Animation() {

	}

	void Animation::NextFrame() {
		if (!mIsLoop && mCurrentFrameIdx == mTextures.size() - 1) {
			return;
		}

		mCurrentFrameIdx++;

		if (mCurrentFrameIdx >= mTextures.size()) {
			mCurrentFrameIdx -= mTextures.size();
		}
	}

	void Animation::AddTexture(Texture2D* texture)
	{
		mTextures.emplace_back(texture);
	}

	void Animation::Release() {
		for (Texture2D* texture : mTextures) {
			texture->Release();
		}
		mTextures.clear();
		//AnimationResourceManager::Get().FreeAnimation(this);
	}

	Texture2D* Animation::AddTexture(const std::string& filepath)
	{
		Texture2D* texture = Texture2D::Create(filepath);
		mTextures.emplace_back(texture);

		return texture;
	}

	void Animation::RemoveTexture(Texture2D* texture)
	{
		auto iter = std::find(mTextures.begin(), mTextures.end(), texture);
		if (iter != mTextures.end()) {
			mTextures.erase(iter);
		}
	}

	void Animation::RemoveTexture(const std::string& name)
	{
		auto iter = mTextures.begin();
		for (; iter != mTextures.end(); iter++) {
			if ((*iter)->GetName() == name) {
				break;
			}
		}

		if (iter != mTextures.end()) {
			mTextures.erase(iter);
		}
	}
	
	void Animation::RemoveTexture(UUID nameHashID)
	{
		auto iter = mTextures.begin();
		for (; iter != mTextures.end(); iter++) {
			if (GetHashID((*iter)->GetName()) == nameHashID) {
				break;
			}
		}

		if (iter != mTextures.end()) {
			mTextures.erase(iter);
		}
	}

	Texture2D* Animation::GetTexture(uint16_t idx) const
	{
		if (idx >= mTextures.size()) {
			CORE_LOG_WARN("Animation {0} has {1} frames, but accessed at an invalid index {2}", mName, mTextures.size(), idx);
			return nullptr;
		}

		return mTextures[idx];
	}
}