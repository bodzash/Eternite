#pragma once
#include "Core/Layer.h"

namespace Apex {

	enum class ImGuiLayerFonts { Bold = 0, Regular };

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void Begin();
		void End();	

		void SetDarkThemeColors();

	private:
		float m_Time = 0.f;
	};

}