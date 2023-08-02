#include "hnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hana
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
