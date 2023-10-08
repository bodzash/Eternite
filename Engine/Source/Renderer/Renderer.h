#pragma once
#include "Camera.h"

// TODO: should be filled with lot of static funcs

namespace Apex {

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit();

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};


}