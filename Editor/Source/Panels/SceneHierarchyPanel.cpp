#include "SceneHierarchyPanel.h"
#include <imgui.h>

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

        // registry.each doesnt work for some reason :)
        auto view = m_Context->m_Registry.view<TagComponent>();
        for (auto e : view)
        {
            Entity entity = { e, m_Context.get() };

            auto& tc = entity.GetComponent<TagComponent>();

            ImGui::Text("%s", tc.Tag.c_str());
        }

        ImGui::End();
    }
}
