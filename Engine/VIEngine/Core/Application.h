#pragma once

namespace VIEngine {
	struct ApplicationConfiguration {
		int Width, Height;
		const char* Title;
	};

	class Application {
	public:
		virtual ~Application() = default;
		virtual bool Init() { return true; }
		void Run();
		virtual void Shutdown() {}
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
	private:
		ApplicationConfiguration mConfig;
	};

	extern Application* CreateApplication();
}