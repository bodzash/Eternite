#include "EditorLayer.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scripts/CameraController.h"

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

void EditorLayer::OnAttach()
{
    m_Scene = CreateRef<Scene>();

    m_Scene->OnRuntimeStart();

    // Scene Camera
    Entity cam = m_Scene->CreateEntity("Camera");
    cam.AddComponent<ScriptComponent>().Bind<CameraController>();
    cam.AddComponent<CameraComponent>().Primary = true;

    // Player
    Entity ent = m_Scene->CreateEntity("Player");
    ent.AddComponent<ModelComponent>("Data/Models/Leblanc/Leblanc_Skin04.gltf",
        "Data/Models/Leblanc/leblanc_Skin04_TX_CM.png");
    ent.AddComponent<RigidBodyComponent>();
    ent.AddComponent<BoxColliderComponent>();

    m_HierarchyPanel.SetContext(m_Scene);
}

void EditorLayer::OnDetach()
{
    m_Scene->OnRuntimeStop();
}

void EditorLayer::OnUpdate(Timestep ts)
{
    m_Scene->OnUpdate(ts);
}

void EditorLayer::OnImGuiRender()
{
    static bool dockspaceOpen = true;
    static bool fullscreenPersistant = true;
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
    bool optFullscreen = fullscreenPersistant;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (optFullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
    {
        windowFlags |= ImGuiWindowFlags_NoBackground;
    }

    // Important: read the imgui docking example
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &dockspaceOpen, windowFlags); // Dockspace
    ImGui::PopStyleVar();

    if (optFullscreen)
    {
        ImGui::PopStyleVar(2);
    }

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    //ImGuiStyle& style = ImGui::GetStyle();
    //float minWinSizeX = style.WindowMinSize.x;
    //style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }

    //style.WindowMinSize.x = minWinSizeX;

    if (ImGui::BeginMenuBar()) // MenuBar
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load Project", "Ctrl+O"))
            {
                AX_INFO("Loading project...");
            }

            if (ImGui::MenuItem("Save Project", "Ctrl+S"))
            {
                AX_INFO("Saving project...");
            }

            if (ImGui::MenuItem("Exit", ""))
            {
                Application::Get().Close();
            }

            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar(); // MenuBar

    ImGui::End(); // Dockspace

    /*
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport"); // Viewport
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (m_ViewportSize != *((glm::vec2*) &viewportPanelSize))
    {
        // Recreate framebuffer
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
    }

    ImGui::Image((ImTextureID)&m_ViewportTexture.texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
    ImGui::End(); // Viewport
    ImGui::PopStyleVar();
    */
    /*
    ImGui::Begin("Inspector"); // Inspector
    ImGui::Text("Placeholder");
    //ImGui::Image((ImTextureID)&m_TestTexture, ImVec2{ 256.0f, 256.0f });
    ImGui::End(); // Inspector
    */

    // Panels
    m_HierarchyPanel.OnImGuiRender();
}