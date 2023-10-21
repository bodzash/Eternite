#pragma once
#include <Apex.h>

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

class CameraController : public NativeBehaviour
{
public:
	bool Enabled = false;

	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
		if (Raylib::IsMouseButtonPressed(Mouse::Right))
		{
			Enabled = !Enabled;

			if (Enabled)
			{
				//Raylib::HideCursor();
				Raylib::DisableCursor();
			}
			else
			{
				//Raylib::ShowCursor();
				Raylib::EnableCursor();
			}
		}

		if (Enabled)
		{
			auto& cc = GetComponent<CameraComponent>();
			Raylib::UpdateCamera(&cc.Camera, Raylib::CAMERA_FREE);
		}
	}

	void OnDestroy() override
	{
	}
};