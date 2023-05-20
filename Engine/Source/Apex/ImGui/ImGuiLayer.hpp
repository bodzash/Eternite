#pragma once
#include "Apex/Layer.hpp"

namespace Apex
{

  class APEX_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnImgGuiRender();
  private:
    float m_Time = 0.f;
  };

}