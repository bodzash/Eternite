#pragma once

#ifdef AX_PLATFORM_WINDOWS

extern Apex::Application* Apex::CreateApplication();

int main(int argc, char** argv)
{
  Apex::Log::Init();
  AX_CORE_ERROR("Damn that shit hurt");
  int a = 32;
  AX_WARN("Not enough dog {0}", a);

  auto* App = Apex::CreateApplication();
  App->Run();
  delete App;
}

#endif