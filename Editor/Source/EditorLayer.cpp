#include "EditorLayer.h"
#include "FileDialog/FileDialog.h"
#include "Scripts/EditorCameraController.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Scene/SceneSerializer.h>
#include <ImGuizmo.h>

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

void EditorLayer::OnAttach()
{
    m_Scene = CreateRef<Scene>();
    m_Scene->OnRuntimeStart();

    // Editor Camera - NO DELETE
    Entity edcam = m_Scene->CreateEntity("EditorCamera");
    edcam.RemoveComponent<TagComponent>();
    edcam.AddComponent<ScriptComponent>().Bind<EditorCameraController>();
    edcam.AddComponent<CameraComponent>().Primary = true;

    // Scene Camera
    Entity cam = m_Scene->CreateEntity("Camera");
    cam.AddComponent<CameraComponent>();

    // Player
    Entity ent = m_Scene->CreateEntity("Player");
    ent.AddComponent<ModelComponent>("Data/Models/Leblanc/Leblanc_Skin04.gltf",
        "Data/Models/Leblanc/leblanc_Skin04_TX_CM.png");
    //ent.AddComponent<RigidBodyComponent>();
    //ent.AddComponent<BoxColliderComponent>();

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
            if (ImGui::MenuItem("New Project", "Ctrl+N"))
            {
                m_Scene = CreateRef<Scene>();
                m_HierarchyPanel.SetContext(m_Scene);
                Entity edcam = m_Scene->CreateEntity("EditorCamera");
                edcam.RemoveComponent<TagComponent>();
                edcam.AddComponent<ScriptComponent>().Bind<EditorCameraController>();
                edcam.AddComponent<CameraComponent>().Primary = true;
            }

            if (ImGui::MenuItem("Load Project", "Ctrl+O"))
            {
                auto path = FileDialog::OpenFile("Apex Scene (*.ascn)\0*.ascn\0");
                if (!path.empty())
                {
                    m_Scene = CreateRef<Scene>();
                    m_HierarchyPanel.SetContext(m_Scene);
                    Entity edcam = m_Scene->CreateEntity("EditorCamera");
                    edcam.RemoveComponent<TagComponent>();
                    edcam.AddComponent<ScriptComponent>().Bind<EditorCameraController>();
                    edcam.AddComponent<CameraComponent>().Primary = true;

                    SceneSerializer serializer(m_Scene);
                    serializer.DeserializeText(path);
                }
            }

            if (ImGui::MenuItem("Save Project", "Ctrl+S"))
            {
                /*
                SceneSerializer serializer(m_Scene);
                serializer.SerializeText("Data/Scenes/Default.ascn");
                */
            }

            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
            {
                auto path = FileDialog::SaveFile("Apex Scene (*.ascn)\0*.ascn\0");
                if (!path.empty())
                {
                    SceneSerializer serializer(m_Scene);
                    serializer.SerializeText(path);
                }
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

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport"); // Viewport

    // Gizmos
    Entity selectedEntity = m_HierarchyPanel.GetSelectedEntity();
    if (selectedEntity)
    {
        //ImGuizmo::SetOrthographic(false);
        //ImGuizmo::SetDrawList();
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x ImGui::GetWindowPos().y, windowWidth, windowHeight);

        auto cameraEntity = Entity{ 0, m_Scene.get() };
        const auto& camera cameraEntity.GetComponent<CameraComponent>();
        glm::mat4 cameraView = glm::inverse((glm::mat4)Raylib::GetCameraMatrix(camera.Camera));

        // Selected
        auto& tc = selectedEntity.GetComponent<TransformComponent>();

        //ImGuizmo::Manipulate();
    }

    ImGui::End(); // Viewport
    ImGui::PopStyleVar();

    ImGui::Begin("Settings");
    ImGui::Text("FPS: %d", Raylib::GetFPS());
    ImGui::Text("Press F1 to toggle camera controls");
    ImGui::End();

    // Panels
    m_HierarchyPanel.OnImGuiRender();
}