#pragma once
#include "Core/Layer.h"

namespace Apex {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.f;
	};

}