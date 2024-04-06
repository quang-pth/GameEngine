#include<VIEngine/Core/Entry.h>
#include<VIEngine/Window/Window.h>
#include<Core/Logger/Logger.h>

#include"EditorLayer.h"

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
	}

	virtual void OnInitClient() override {
		LOG_INFO("Game is init");

		mUILayer = new UILayer();
		PushOverlayLayer(mUILayer);
		
		mGameplayLayer = new GameplayLayer();
		PushLayer(mGameplayLayer);
	}

	virtual void OnShutdownClient() override {
		PopLayer(mGameplayLayer);
		PopLayer(mUILayer);

		LOG_INFO("Game is shutdown");
	}
private:
	VIEngine::Layer* mUILayer, *mGameplayLayer;
};

VIEngine::Application* VIEngine::CreateApplication() {
	VIEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngine Alpha ver";
	appConfig.WindowSpec = VIEngine::EWindowPlatformSpec::GLFW;

	return new Game(appConfig);
}