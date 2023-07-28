#pragma once

#include "Hana/Core/Layer.h"

#include "Hana/Events/ApplicationEvent.h"
#include "Hana/Events/KeyEvent.h"
#include "Hana/Events/MouseEvent.h"

namespace Hana
{
	class HANA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
