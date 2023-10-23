#include "HierarchyPanel.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

namespace Apex {

    HierarchyPanel::HierarchyPanel(const Ref<Scene>& context)
    {
        SetContext(context);
    }

    void HierarchyPanel::SetContext(const Ref<Scene>& context)
    {
        m_Context = context;
    }

    void HierarchyPanel::OnImGuiRender()
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

        // TODO: change it to a button at the bottom of the panel
        if (ImGui::BeginPopupContextWindow("", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Create Entity"))
            {
                m_SelectionContext = m_Context->CreateEntity();
            }

            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("Inspector");

        if (m_SelectionContext)
        {
            RenderComponents(m_SelectionContext);

            
        }

        ImGui::End();
    }

    void HierarchyPanel::RenderEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        bool entityDeleted = false;
        std::string uniqeId = tag;
        uniqeId += (uint32_t)entity;
        if (ImGui::BeginPopupContextItem(uniqeId.c_str(), ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if (opened)
        {
            // TODO: Recursively go trough children
            ImGui::TreePop();
        }

        if (entityDeleted)
        {
            m_Context->DestroyEntity(entity);
            if (m_SelectionContext == entity)
                m_SelectionContext = {};
        }
    }

    static void RenderVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());

        ImGui::NextColumn();
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
        ImVec2 buttonSize = { lineHeight + 3.f, lineHeight };


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.f, 0.f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.82, 0.7f, 0.3f, 1.f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.f, 0.f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.3f, 0.9f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.f, 0.f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    template<typename T, typename UIFunction>
    static void RenderComponent(const std::string& name, Entity entity, UIFunction fn)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        if (entity.HasComponent<T>())
        {
            auto& component = entity.GetComponent<T>();
            ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();

            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();
            ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
            if (ImGui::Button("...", ImVec2{ lineHeight, lineHeight }))
            {
                ImGui::OpenPopup("ComponentSettings");
            }

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove Component"))
                    removeComponent = true;
                ImGui::EndPopup();
            }

            if (open)
            {
                fn(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                entity.RemoveComponent<T>();
        }
    }

    void HierarchyPanel::RenderComponents(Entity entity)
    {
        // TagComponent
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>().Tag;
            
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            if (ImGui::MenuItem("Camera"))
            {
                m_SelectionContext.AddComponent<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Model"))
            {
                m_SelectionContext.AddComponent<ModelComponent>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
        ImGui::PopItemWidth();

        RenderComponent<TransformComponent>("Transform", entity, [](auto& component)
        {
            RenderVec3Control("Translation", component.Translation);
            RenderVec3Control("Rotation", component.Rotation);
            RenderVec3Control("Scale", component.Scale, 1.0f);
        });

        RenderComponent<CameraComponent>("Camera", entity, [](auto& component)
        {
            ImGui::Checkbox("Primary", &component.Primary);

            const char* projTypeStrings[] = { "Perspective", "Orthographic" };
            // TODO: get proj type
            // TODO: implement SceneCamera (its a raylib Camera3D wrapper really...)
            const char* currentProjTypeString = projTypeStrings[0];

            if (ImGui::BeginCombo("Projection", currentProjTypeString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool selected = currentProjTypeString == projTypeStrings[i];
                    if (ImGui::Selectable(projTypeStrings[i], selected))
                    {
                        currentProjTypeString = projTypeStrings[i];
                        // TODO: set proj type to [i]
                    }
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            /*
            if persp -> display persp stuff
            if orthi -> display ortho stuff
            */
        });

        RenderComponent<ModelComponent>("Model", entity, [](auto& component)
        {
            ImGui::Text(component.ModelPath.c_str());
            ImGui::Text(component.TexturePath.c_str());
            //ImGui::Image((ImTextureID)&mc.Texture, ImVec2{ 128.0f, 128.f });
            ImGui::Text(component.AnimationPath.c_str());
        });
    }
}
