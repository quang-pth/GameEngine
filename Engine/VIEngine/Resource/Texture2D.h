#pragma once

#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"

namespace VIEngine {
	struct VI_API TextureData {
		const char* Name;
		uint32_t Width, Height;
		void* Data;
		ETextureFormat InternalFormat, ImageFormat;
		ETextureWrapMode HorizontalWrap = ETextureWrapMode::Repeat;
		ETextureWrapMode VerticalWrap = ETextureWrapMode::Repeat;
		ETextureFilter MinFilter = ETextureFilter::Linear;
		ETextureFilter MagFilter = ETextureFilter::Linear;
		uint8_t NumberOfChannels;
		bool Alpha;
	};

	class VI_API Texture2D : public Object {
	public:
		DECLARE_RTTI
	public:
		static Texture2D* Create(const std::string& filepath, bool alpha = true);
	public:
		virtual ~Texture2D() = default;

		virtual void Release() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() const = 0;
		virtual const char* GetName() const = 0;
		virtual void SetName(const char* name) = 0;
		virtual const TextureData& GetTextureData() const = 0;
		virtual void SetWrapMode(ETextureWrapMode horizontal, ETextureWrapMode vertical) = 0;
		// Set border color for a texture. This option only affects if texture wrap mode is set to ETextureWrapMode::Border
		virtual void SetBorderColor(float r, float g, float b, float w = 1.0f) = 0;
		virtual void SetFilter(ETextureFilter min, ETextureFilter mag) = 0;
	protected:
		Texture2D() = default;
	};
}