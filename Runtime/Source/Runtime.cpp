#include <axpch.hpp>
#include <Apex.hpp>

class Runtime : public Apex::Application
{
public:
  Runtime() {}
  ~Runtime() {}
};

Apex::Application* Apex::CreateApplication()
{
  return new Runtime();
}