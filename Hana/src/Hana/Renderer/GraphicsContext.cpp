#include "hnpch.h"
#include "Hana/Renderer/GraphicsContext.h"

#include "Hana/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Hana
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	HN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		HN_CORE_ASSERT(false, "Unkonwn RendererAPI!");
		return nullptr;
	}
}
