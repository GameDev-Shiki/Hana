#pragma once

#include "Hana.h"

class Sandbox2D : public Hana::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hana::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hana::Event& e) override;
private:
	Hana::OrthographicCameraController m_CameraController;

	// Temp
	Hana::Ref<Hana::VertexArray> m_SquareVA;
	Hana::Ref<Hana::Shader> m_FlatColorShader;

	Hana::Ref<Hana::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};

