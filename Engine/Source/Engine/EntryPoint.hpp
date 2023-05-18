#pragma once

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
  Engine::Log::Init();
  EN_CORE_ERROR("Damn that shit hurt");
  int a = 32;
  EN_WARN("Not enough dog {0}", a);

  auto* App = Engine::CreateApplication();
  App->Run();
  delete App;
}

#endif