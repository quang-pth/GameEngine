#pragma once

#include"pch.h"

namespace VIEngine {
	class Sprite;

	class VI_API Animation {
	public:
		static Animation* Create(const std::string& name);
	public:
		Animation(const std::string& name);
		~Animation();
		void NextFrame();
		Sprite* AddSprite(const std::string& filepath);
		void Release();
		void RemoveSprite(const std::string& name);
		void RemoveSprite(UUID nameHashID);
		Sprite* GetSprite(uint16_t idx) const;
		std::vector<Sprite*>& GetSprites() { return mSprites; }
		VI_FORCE_INLINE Sprite* CurrentFrame() const { return mSprites[mCurrentFrameIdx]; }
		VI_FORCE_INLINE size_t GetNumsFrame() const { return mSprites.size(); }
		VI_FORCE_INLINE const std::string& GetName() const { return mName; }
		VI_FORCE_INLINE void SetName(const std::string& name) { mName = name; mNameHashID = GetHashID(name); }
		VI_FORCE_INLINE bool GetIsLoop() const { return mIsLoop; }
		VI_FORCE_INLINE void SetIsLoop(bool isLoop) { mIsLoop = isLoop; }
	private:
		std::vector<Sprite*> mSprites;
		std::string mName;
		UUID mNameHashID;
		size_t mCurrentFrameIdx;
		bool mIsLoop;
	};
}