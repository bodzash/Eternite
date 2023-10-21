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

		ImGui::StyleColorsDark();

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

}