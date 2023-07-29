#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1920.f / 1080.f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Hana::VertexArray::Create();

	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Hana::Ref<Hana::VertexBuffer> squareVB;
	squareVB = Hana::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout(
		{
			{ Hana::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Hana::Ref<Hana::IndexBuffer> squareIB;
	squareIB = Hana::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Hana::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hana::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hana::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hana::RenderCommand::Clear();

	Hana::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Hana::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Hana::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Hana::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hana::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hana::Event& e)
{
	m_CameraController.OnEvent(e);
}
