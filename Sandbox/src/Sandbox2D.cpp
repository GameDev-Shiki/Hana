#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1920.f / 1080.f)
{
}

void Sandbox2D::OnAttach()
{
	HN_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hana::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	HN_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Hana::Timestep ts)
{
	HN_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		HN_PROFILE_SCOPE("Renderer Prep");
		Hana::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hana::RenderCommand::Clear();
	}

	{
		HN_PROFILE_SCOPE("Renderer Draw");
		Hana::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hana::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Hana::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Hana::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Hana::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HN_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Hana::Event& e)
{
	m_CameraController.OnEvent(e);
}
