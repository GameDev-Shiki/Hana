#pragma once

#include "Hana.h"

class ExampleLayer : public Hana::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hana::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hana::Event& e) override;

private:
	Hana::ShaderLibrary m_ShaderLibrary;
	Hana::Ref<Hana::Shader> m_Shader;
	Hana::Ref<Hana::VertexArray> m_VertexArray;

	Hana::Ref<Hana::Shader> m_FlatColorShader;
	Hana::Ref<Hana::VertexArray> m_SquareVA;

	Hana::Ref<Hana::Texture2D> m_Texture;
	Hana::Ref<Hana::Texture2D> m_ElfTexture;

	Hana::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
