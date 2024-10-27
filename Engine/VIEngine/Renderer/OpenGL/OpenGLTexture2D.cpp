#include"OpenGLTexture2D.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLTexture2D, Texture2D::RunTimeType)

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath, bool alpha) : mID(), mData() {
		mData = ResourceManager::Get().LoadImageFromFile(filepath, alpha);
		Renderer::Submit([this, filepath, alpha]() {
			glGenTextures(1, &mID);
			glBindTexture(GL_TEXTURE_2D, mID);
			glTexImage2D(GL_TEXTURE_2D, 0, OpenGLFactory::ToOpenGLFormat(mData.InternalFormat),
				mData.Width, mData.Height, 0, OpenGLFactory::ToOpenGLFormat(mData.ImageFormat), GL_UNSIGNED_BYTE, mData.Data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			ResourceManager::Get().FreeImageData(mData.Data);
		});
	}

	OpenGLTexture2D::~OpenGLTexture2D() {

	}

	void OpenGLTexture2D::Release() {
		Renderer::Submit([this]() {
			glDeleteTextures(1, &mID);
			ResourceManager::Get().FreeTexture2D(this);
		});
	}

	void OpenGLTexture2D::Bind() {
		Renderer::Submit([this]() {
			glBindTexture(GL_TEXTURE_2D, mID);
			glActiveTexture(GL_TEXTURE0);
		});
	}

	void OpenGLTexture2D::Unbind() {
		Renderer::Submit([]() {
			glBindTexture(GL_TEXTURE_2D, 0);
		});
	}
	void OpenGLTexture2D::SetWrapMode(ETextureWrapMode horizontal, ETextureWrapMode vertical)
	{
		Renderer::Submit([this, horizontal, vertical]() {
			if (horizontal != mData.HorizontalWrap) {
				glBindTexture(GL_TEXTURE_2D, mID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OpenGLFactory::ToOpenGLWrapMode(horizontal));
				mData.HorizontalWrap = horizontal;
			}

			if (vertical != mData.VerticalWrap) {
				glBindTexture(GL_TEXTURE_2D, mID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OpenGLFactory::ToOpenGLWrapMode(vertical));
				mData.VerticalWrap = vertical;
			}
		});
	}

	void OpenGLTexture2D::SetBorderColor(float r, float g, float b, float w)
	{
		Renderer::Submit([this, r, g, b, w]() {
			glBindTexture(GL_TEXTURE_2D, mID);
			float borderColor[] = { r, g, b, w };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		});
	}

	void OpenGLTexture2D::SetFilter(ETextureFilter min, ETextureFilter mag)
	{
		Renderer::Submit([this, min, mag]() {
			if (min != mData.MinFilter) {
				glBindTexture(GL_TEXTURE_2D, mID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OpenGLFactory::ToOpenGLTextureFilter(min));
				mData.MinFilter = min;
			}

			if (mag != mData.MinFilter) {
				glBindTexture(GL_TEXTURE_2D, mID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OpenGLFactory::ToOpenGLTextureFilter(mag));
				mData.MagFilter = mag;
			}
		});
	}
}