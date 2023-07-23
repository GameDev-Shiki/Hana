#include <Hana.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hana::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
		, m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hana::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Hana::Ref<Hana::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hana::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hana::BufferLayout layout =
		{
			{ Hana::ShaderDataType::Float3, "a_Position" },
			{ Hana::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Hana::Ref<Hana::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hana::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Hana::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hana::Ref<Hana::VertexBuffer> squareVB;
		squareVB.reset(Hana::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(
			{
				{ Hana::ShaderDataType::Float3, "a_Position" },
				{ Hana::ShaderDataType::Float2, "a_TexCoord" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Hana::Ref<Hana::IndexBuffer> squareIB;
		squareIB.reset(Hana::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Hana::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Hana::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Hana::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Hana::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ElfTexture = Hana::Texture2D::Create("assets/textures/elf.png");

		std::dynamic_pointer_cast<Hana::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hana::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hana::Timestep ts) override
	{
		if (Hana::Input::IsKeyPressed(HN_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Hana::Input::IsKeyPressed(HN_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Hana::Input::IsKeyPressed(HN_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Hana::Input::IsKeyPressed(HN_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Hana::Input::IsKeyPressed(HN_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Hana::Input::IsKeyPressed(HN_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Hana::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hana::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hana::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Hana::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Hana::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y)
		{ 
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hana::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Hana::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ElfTexture->Bind();
		Hana::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Hana::Renderer::Submit(m_Shader, m_VertexArray);

		Hana::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hana::Event& event) override
	{
	}

private:
	Hana::Ref<Hana::Shader> m_Shader;
	Hana::Ref<Hana::VertexArray> m_VertexArray;

	Hana::Ref<Hana::Shader> m_FlatColorShader;
	Hana::Ref<Hana::Shader> m_TextureShader;
	Hana::Ref<Hana::VertexArray> m_SquareVA;

	Hana::Ref<Hana::Texture2D> m_Texture;
	Hana::Ref<Hana::Texture2D> m_ElfTexture;

	Hana::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Hana::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hana::Application* Hana::CreateApplication()
{
	return new Sandbox();
}
