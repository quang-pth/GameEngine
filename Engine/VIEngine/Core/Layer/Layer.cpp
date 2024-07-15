#include"Layer.h"
#include"Core/Application.h"

namespace VIEngine {
	Layer::Layer() 
		: 
		mID(GetUUID()),
		mRenderer(Application::Get().GetRendererer()),
		mScene(Application::Get().GetCurrentActiveScene())
	{

	}
}