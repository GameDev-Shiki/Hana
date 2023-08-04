#pragma once
#include "Hana/Core/Core.h"

#ifdef HN_PLATFORM_WINDOWS

extern Hana::Application* Hana::CreateApplication();

int main(int argc, char** argv)
{
	Hana::Log::Init();

	HN_PROFILE_BEGIN_SESSION("Startup", "HanaProfile-Startup.json");
	auto app = Hana::CreateApplication();
	HN_PROFILE_END_SESSION();

	HN_PROFILE_BEGIN_SESSION("Runtime", "HanaProfile-Runtime.json");
	app->Run();
	HN_PROFILE_END_SESSION();

	HN_PROFILE_BEGIN_SESSION("Shutdown", "HanaProfile-Shutdown.json");
	delete app;
	HN_PROFILE_END_SESSION();
}

#endif
