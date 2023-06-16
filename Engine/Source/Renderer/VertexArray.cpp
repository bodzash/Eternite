#include "axpch.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
// TODO: remove abstraction

namespace Apex
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		AX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}