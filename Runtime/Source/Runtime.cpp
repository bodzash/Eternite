#include <iostream>
#include <Engine.hpp>

class App : public Engine::Application
{
public:
  App() {}
  ~App() {}
};

int main()
{
  App* app = new App();
  app->Run();
  delete app;
}