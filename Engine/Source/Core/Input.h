#pragma once
#include "Core.h"

namespace Apex {

	class Input
	{
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	private:
		Input() = default;
		static Input* s_Instance;
	};

}