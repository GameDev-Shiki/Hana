#include "hnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hana
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
