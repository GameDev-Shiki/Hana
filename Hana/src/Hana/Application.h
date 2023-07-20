#pragma once

#include "Core.h"

#include "Window.h"
#include "Hana/LayerStack.h"
#include "Hana/Events/Event.h"
#include "Hana/Events/ApplicationEvent.h"

#include "Hana/Core/Timestep.h"

#include "Hana/ImGui/ImGuiLayer.h"

namespace Hana
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;
	
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in the client
	Application* CreateApplication();
}
