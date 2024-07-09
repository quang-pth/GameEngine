#include"RendererAPIFactory.h"
#include"OpenGLRendererAPI.h"

namespace VIEngine {
	RendererAPI* RendererAPIFactory::CreateRendererAPI(ERendererAPI apiSpec) {
		RendererAPI* api = nullptr;

		switch (apiSpec)
		{
			case ERendererAPI::OpenGL: api = new OpenGLRendererAPI(); break;
			case ERendererAPI::DirectX: break;
			default: break;
		}

		return api;
	}
}
