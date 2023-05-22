#pragma once
#include "Apex/Layer.hpp"

namespace Apex
{

  class APEX_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer() = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnImGuiRender() override;

    void Begin();
    void End();
  private:
    float m_Time = 0.f;
  };

}