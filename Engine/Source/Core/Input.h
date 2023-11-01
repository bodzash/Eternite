#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"
#include <glm/glm.hpp>

namespace Apex {

	class Input
	{
	public:
		Input() = delete;

		static bool IsKeyPressed(KeyCode key);
		static bool IsKeyDown(KeyCode key);
		static bool IsKeyReleased(KeyCode key);
		static bool IsKeyUp(KeyCode key);
		static KeyCode GetKeyPressed();
    	static KeyCode GetCharPressed();

		static bool IsMousePressed(MouseCode button);
		static bool IsMouseDown(MouseCode button);
		static bool IsMouseReleased(MouseCode button);
		static bool IsMouseUp(MouseCode button);

		static glm::vec2 GetMousePosition();
		static glm::vec2 GetMouseWheelMove();
		static float GetMouseX();
		static float GetMouseY();

		/*
		Implement these only if needed for some reason
		static glm::vec2 GetMouseDelta();
		static void SetMousePosition(int x, int y);
		static void SetMouseOffset(int offsetX, int offsetY);
		static void SetMouseScale(float scaleX, float scaleY);
		static float GetMouseWheelMove();
		static glm::vec2 GetMouseWheelMoveV();
		static void SetMouseCursor(int cursor); 
		*/
	};

}