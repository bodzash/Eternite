#pragma once
#include <Apex.h>

namespace Apex {

    class HierarchyPanel
    {
    public:
        HierarchyPanel() = default;
        HierarchyPanel(const Ref<Scene>& context);

        void SetContext(const Ref<Scene>& context);
        void OnImGuiRender();
        Entity GetSelectedEntity() const { return m_SelectionContext; }

    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;

        void RenderEntityNode(Entity entity);
        void RenderComponents(Entity entity);
    };

}
