#pragma once
#include "Hana/Core/Core.h"

#ifdef HN_PLATFORM_WINDOWS

extern Hana::Application* Hana::CreateApplication();

int main(int argc, char** argv)
{
	Hana::Log::Init();
	HN_CORE_INFO("Initialized Log!");

	auto app = Hana::CreateApplication();
	app->Run();
	delete app;
}

#endif
