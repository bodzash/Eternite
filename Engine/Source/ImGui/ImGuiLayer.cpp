#include "axpch.h"
#include "Core/Application.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include "rlImGui.h"

namespace Apex
{

	ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiLayer") {}

	void ImGuiLayer::OnAttach()
	{
		rlImGuiSetup(true);
		
		/*
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;        // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();


		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOther(window, true);
		ImGui_Implbgfx_Init(0);
		*/
	}

	void ImGuiLayer::OnDetach()
	{
		/*
		ImGui_Implbgfx_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		*/
		rlImGuiShutdown();
	}

	void ImGuiLayer::Begin()
	{
		/*
		ImGui_Implbgfx_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		*/
		rlImGuiBegin();
	}

	void ImGuiLayer::End()
	{
		/*
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
		*/
		ImGui::ShowDemoWindow();

		rlImGuiEnd();
	}

}