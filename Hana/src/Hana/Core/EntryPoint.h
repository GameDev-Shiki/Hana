#pragma once

#ifdef HN_PLATFORM_WINDOWS

extern Hana::Application* Hana::CreateApplication();

int main(int argc, char** argv)
{
	Hana::Log::Init();
	HN_CORE_WARN("Initialized Log!");
	int a = 5;
	HN_INFO("Hello! Var={0}", a);

	auto app = Hana::CreateApplication();
	app->Run();
	delete app;
}

#endif
