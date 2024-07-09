#pragma once

#include"RendererAPI.h"
#include"Resource/Resource.h"

namespace VIEngine {
	class RendererAPIFactory {
	public:
		static RendererAPI* CreateRendererAPI(ERendererAPI api);
	};
}