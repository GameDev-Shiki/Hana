#include <Hana.h>
#include <Hana/Core/EntryPoint.h>

#include "ExampleLayer.h"

#include "Sandbox2D.h"

class Sandbox : public Hana::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hana::Application* Hana::CreateApplication()
{
	return new Sandbox();
}
