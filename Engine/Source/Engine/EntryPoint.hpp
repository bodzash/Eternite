#pragma once

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
  auto* App = Engine::CreateApplication();
  App->Run();
  delete App;
}

#endif