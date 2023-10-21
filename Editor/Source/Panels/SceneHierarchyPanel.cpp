#include "SceneHierarchyPanel.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Apex {

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
    {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
    {
        m_Context = context;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Hierarchy");

        auto view = m_Context->m_Registry.view<TagComponent>();
        for (auto e : view)
        {
            Entity entity = { e, m_Context.get() };
            RenderEntityNode(entity);
        }

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            m_SelectionContext = {};
        }

        ImGui::End();

        ImGui::Begin("Inspector");

        if (m_SelectionContext)
        {
            RenderComponents(m_SelectionContext);
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::RenderEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        if (opened)
        {
            // Recursively go trough children
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::RenderComponents(Entity entity)
    {
        // TagComponent
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>().Tag;
            
            char buffer[128];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        // TransformComponent
        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& tc = entity.GetComponent<TransformComponent>();
                ImGui::DragFloat3("Translation", glm::value_ptr(tc.Translation), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(tc.Rotation), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(tc.Scale), 0.1f);

                ImGui::TreePop();
            }
        }
    }
}
