#include "axpch.h"
#include "Renderer.h"

namespace Raylib {
	#include <raylib.h>
}

namespace Apex {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit()
	{
	}
}