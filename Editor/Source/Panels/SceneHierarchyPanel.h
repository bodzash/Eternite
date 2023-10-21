#pragma once
#include <Apex.h>

namespace Apex {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& context);

        void SetContext(const Ref<Scene>& context);
        void OnImGuiRender();

    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;

        void RenderEntityNode(Entity entity);
        void RenderComponents(Entity entity);
    };

}
