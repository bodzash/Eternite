#include "axpch.hpp"
#include "Apex/Application.hpp"
#include "ImGuiLayer.hpp"
#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.hpp"
//#include "backends/imgui_impl_glfw.h"
//#include "backends/imgui_impl_opengl2.h"
#include "GLFW/glfw3.h"

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
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    //ImGui_ImplGlfw_InitForOpenGL(, true);
    ImGui_ImplOpenGL2_Init();
  }

  void ImGuiLayer::OnDetach()
  {
  }

  void ImGuiLayer::OnUpdate()
  {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetWidth());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.f / 60.f);
    m_Time = time;

    ImGui_ImplOpenGL2_NewFrame();
    ImGui::NewFrame();


    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGuiLayer::OnEvent(Event& event)
  {

  }


}