#pragma once
#include "Core.h"
#include <glm/glm.hpp>

namespace Apex {

	class Input
	{
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(int key);
		static bool IsKeyDown(int key);
		static bool IsKeyReleased(int key);
		static bool IsKeyUp(int key);

		static bool IsMousePressed(int button);
		static bool IsMouseButtonDown(int button);
		static bool IsMouseButtonReleased(int button);
		static bool IsMouseButtonUp(int button);

		static glm::vec2 GetMouseWheelMove();
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	private:
		Input() = default;
		static Input* s_Instance;
	};

}