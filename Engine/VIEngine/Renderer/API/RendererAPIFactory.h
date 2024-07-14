#pragma once

#include"RendererAPI.h"

namespace VIEngine {
	class RendererAPIFactory {
	public:
		static RendererAPI* CreateRendererAPI(ERendererAPI api);
	};
}