#pragma once
#include <Apex.h>
#include <glm/glm.hpp>
#include "Panels/HierarchyPanel.h"

class EditorLayer : public Apex::Layer
{
public:
	EditorLayer()
		: Layer("EditorLayer") {}

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Apex::Timestep ts) override;
	void OnImGuiRender() override;

private:
	Apex::Ref<Apex::Scene> m_Scene;
	glm::vec2 m_ViewportSize;

	// Panels
	Apex::HierarchyPanel m_HierarchyPanel;
};