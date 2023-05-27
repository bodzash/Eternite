#pragma once
#include "Apex/Core.hpp"
#include "Apex/Events/Event.hpp"
#include "Apex/Core/Timestep.hpp"

namespace Apex
{

  class APEX_API Layer
  {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(Timestep ts) {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& event) {}

    inline const std::string& GetName() { return m_DebugName; }
  protected:
    std::string m_DebugName;
  };

}