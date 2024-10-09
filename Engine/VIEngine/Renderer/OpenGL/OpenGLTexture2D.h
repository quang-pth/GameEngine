#pragma once

#include"Resource/Texture2D.h"

namespace VIEngine {
	class OpenGLTexture2D : public Texture2D {
	public:
		DECLARE_RTTI
	public:
		OpenGLTexture2D(const char* filepath, bool alpha);
		~OpenGLTexture2D();
		
		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual const char* GetName() const override { return mData.Name; }
		VI_FORCE_INLINE virtual void SetName(const char* name) override { mData.Name = name; }
		virtual const TextureData& GetTextureData() const override { return mData; }
		virtual void SetWrapMode(ETextureWrapMode horizontal, ETextureWrapMode vertical) override;
		virtual void SetBorderColor(float r, float g, float b, float w = 1.0f) override;
		virtual void SetFilter(ETextureFilter min, ETextureFilter mag) override;
	private:
		uint32_t mID;
		TextureData mData;
	};
}