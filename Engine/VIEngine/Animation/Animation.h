#pragma once

#include"Resource/Texture2D.h"

namespace VIEngine {
	class VI_API Animation {
	public:
		static Animation* Create(const std::string& name);
	public:
		Animation(const std::string& name);
		~Animation();
		void NextFrame();
		void AddTexture(Texture2D* texture);
		void Release();
		Texture2D* AddTexture(const std::string& filepath);
		void RemoveTexture(Texture2D* texture);
		void RemoveTexture(const std::string& name);
		void RemoveTexture(UUID nameHashID);
		Texture2D* GetTexture(uint16_t idx) const;
		VI_FORCE_INLINE Texture2D* CurrentFrame() const { return mTextures[mCurrentFrameIdx]; }
		VI_FORCE_INLINE uint16_t GetNumsFrame() const { return mTextures.size(); }
		VI_FORCE_INLINE const std::string& GetName() const { return mName; }
		VI_FORCE_INLINE void SetName(const std::string& name) { mName = name; mNameHashID = GetHashID(name); }
		VI_FORCE_INLINE bool GetIsLoop() const { return mIsLoop; }
		VI_FORCE_INLINE void SetIsLoop(bool isLoop) { mIsLoop = isLoop; }
	private:
		std::vector<Texture2D*> mTextures;
		std::string mName;
		UUID mNameHashID;
		uint32_t mCurrentFrameIdx;
		bool mIsLoop;
	};
}