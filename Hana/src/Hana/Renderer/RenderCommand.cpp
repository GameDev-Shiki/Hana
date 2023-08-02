#include "hnpch.h"
#include "Hana/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hana
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
