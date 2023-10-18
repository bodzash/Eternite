#include "axpch.h"
#include "Input.h"
#include "Core/Application.h"

namespace Raylib {
	#include <raylib.h>
}

namespace Apex {

	Input* Input::s_Instance = new Input();

	bool Input::IsKeyPressed(int key)
	{
		return Raylib::IsKeyPressed(key);
	}

	bool Input::IsMousePressed(int button)
	{
		return Raylib::IsMouseButtonPressed(button);
	}

	glm::vec2 Input::GetMousePosition()
	{
		Raylib::Vector2 mousePos = Raylib::GetMousePosition();
		return { mousePos.x, mousePos.y };
	}

	float Input::GetMouseX()
	{
		return static_cast<float>(Raylib::GetMouseX());
	}

	float Input::GetMouseY()
	{
		return static_cast<float>(Raylib::GetMouseY());
	}
}