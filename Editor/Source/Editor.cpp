#include <Apex.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

class EditorLayer : public Layer
{
public:
	EditorLayer()
		: Layer("EditorLayer") {}

	void OnAttach() override
	{
		m_Scene.OnRuntimeStart();
		m_TestTexture = Raylib::LoadTexture("Data/Models/Leblanc/leblanc_Skin04_TX_CM.png");
		//m_ViewportTexture = Raylib::LoadRenderTexture(640, 480);
		// Scene Camera
		Entity cam = m_Scene.CreateEntity();
		cam.AddComponent<CameraComponent>().Primary = true;

		// Player
		Entity ent = m_Scene.CreateEntity();
		ent.AddComponent<ModelComponent>("Data/Models/Leblanc/Leblanc_Skin04.gltf",
			"Data/Models/Leblanc/leblanc_Skin04_TX_CM.png");
		ent.AddComponent<RigidBodyComponent>();
		ent.AddComponent<BoxColliderComponent>();
	}

	void OnDetach() override
	{
		m_Scene.OnRuntimeStop();
	}

	void OnUpdate(Timestep ts) override
	{
		m_Scene.OnUpdate(ts);
	}

	void OnImGuiRender() override
	{
		//Raylib::UpdateTexture(m_ViewportTexture, Raylib::LoadImageFromScreen().data);
		/*
		Raylib::BeginTextureMode(m_ViewportTexture);
		Raylib::ClearBackground({255, 0, 0, 255});
		Raylib::EndTextureMode();
		*/

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

		ImGui::Begin("Viewport"); // Viewport
		//ImGui::Image((ImTextureID)&m_ViewportTexture.texture, ImVec2{ 640.0f, 480.0f });
		ImGui::End(); // Viewport


		ImGui::Begin("Inspector"); // Inspector
		ImGui::Text("Placeholder");
		ImGui::ColorEdit3("Test Color", glm::value_ptr(m_TestColor));
		ImGui::Image((ImTextureID)&m_TestTexture, ImVec2{ 256.0f, 256.0f });
		ImGui::End(); // Inspector
	}

private:
	Scene m_Scene;

	glm::vec3 m_TestColor = glm::vec3(0.0f, 1.0f, 0.0f);
	Raylib::Texture2D m_TestTexture;
	Raylib::RenderTexture2D m_ViewportTexture;
	Raylib::Texture2D m_Dawg;
};

class GameEditor : public Application
{
public:
	GameEditor()
	{
		PushLayer(new EditorLayer());
	}
};

Apex::Application* Apex::CreateApplication()
{
	// TODO: ONLY PRESENT IN INTERNAL BUILD, NOT IN DIST
	auto path = std::filesystem::current_path().parent_path().parent_path().parent_path();
	std::filesystem::current_path(path);
	AX_INFO("Path changed: {0}", path);

	return new GameEditor();
}