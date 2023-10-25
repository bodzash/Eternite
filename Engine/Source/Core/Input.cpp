#include "axpch.h"
#include "Input.h"

namespace Raylib {
	#include <raylib.h>
}

namespace Apex {

#pragma region Keyboard

	bool Input::IsKeyPressed(KeyCode key)
	{
		return Raylib::IsKeyPressed(key);
	}

	bool Input::IsKeyDown(KeyCode key)
	{
		return Raylib::IsKeyDown(key);
	}

	bool Input::IsKeyReleased(KeyCode key)
	{
		return Raylib::IsKeyReleased(key);
	}

	bool Input::IsKeyUp(KeyCode key)
	{
		return Raylib::IsKeyUp(key);
	}

	KeyCode Input::GetKeyPressed()
	{
		return Raylib::GetKeyPressed();
	}

	KeyCode Input::GetCharPressed()
	{
		return Raylib::GetCharPressed();
	}

#pragma endregion Keyboard

#pragma region Mouse

	bool Input::IsMousePressed(int button)
	{
		return Raylib::IsMouseButtonPressed(button);
	}

	bool IsMouseDown(MouseCode button)
	{
		return Raylib::IsMouseButtonDown(button);
	}

	bool IsMouseReleased(MouseCode button)
	{
		return Raylib::IsMouseButtonReleased(button);
	}

	bool IsMouseUp(MouseCode button)
	{
		return Raylib::IsMouseButtonUp(button);
	}
	
	glm::vec2 Input::GetMousePosition()
	{
		Raylib::Vector2 mousePos = Raylib::GetMousePosition();
		return { mousePos.x, mousePos.y };
	}

	glm::vec2 Input::GetMouseWheelMove()
	{
		Raylib::Vector2 wheelMove = Raylib::GetMouseWheelMoveV();
		return { wheelMove.x, wheelMove.y };
	}

	float Input::GetMouseX()
	{
		return static_cast<float>(Raylib::GetMouseX());
	}

	float Input::GetMouseY()
	{
		return static_cast<float>(Raylib::GetMouseY());
	}

#pragma endregion Mouse

}