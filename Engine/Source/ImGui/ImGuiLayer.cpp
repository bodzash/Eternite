#include "axpch.h"
#include "Core/Application.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include "rlImGui.h"
#include "imgui_impl_raylib.h"

namespace Raylib {
	#include <raylib.h>
}

namespace Apex
{

	ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiLayer") {}

	void ImGuiLayer::OnAttach()
	{	
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		io.Fonts->AddFontFromFileTTF("Data/Fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("Data/Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

		//ImGui::StyleColorsDark();
		SetDarkThemeColors();
		ImGui_ImplRaylib_Init();
	}

	void ImGuiLayer::OnDetach()
	{
    	ImGui_ImplRaylib_Shutdown();
    	ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();
		ImGui_ImplRaylib_ProcessEvents();
	}

	void ImGuiLayer::End()
	{
		/*
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		*/

		// Rendering
		ImGui::Render();
		ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Resize
		colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.05, 0.46, 0.2, 1.0f };
		colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.05, 0.6, 0.4, 1.0f };
		colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.15, 0.76, 0.5, 1.0f };

		// Action?
		colors[ImGuiCol_CheckMark] = ImVec4{ 0.15, 0.76, 0.5, 1.0f };
		colors[ImGuiCol_TextSelectedBg] = ImVec4{0.15, 0.76, 0.5, 1.0f};
	}

}