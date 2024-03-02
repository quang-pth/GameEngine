#include"Application.h"

int main() {
	VIEngine::Application* application = VIEngine::CreateApplication();

	if (application->Init()) {
		application->Run();
	}

	application->Shutdown();
	VI_FREE_MEMORY(application);
	
	std::cin.get();
	return 0;
}