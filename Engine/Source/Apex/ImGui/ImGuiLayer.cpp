#include "axpch.hpp"
#include "Apex/Application.hpp"
#include "ImGuiLayer.hpp"
#include "imgui.h"

//#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"

namespace Apex
{

  ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
  {
  }

  ImGuiLayer::~ImGuiLayer()
  {
  }

  void ImGuiLayer::OnAttach()
  {
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
    
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();
    
  }

  void ImGuiLayer::OnDetach()
  {
  }

  void ImGuiLayer::OnUpdate()
  {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    /*
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetWidth());

    float time = 12;//(float)glfwGetTime();
    io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.f / 60.f);
    m_Time = time;

    ImGui_ImplOpenGL2_NewFrame();
    ImGui::NewFrame();


    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    */
  }


}