#pragma once

extern Apex::Application* Apex::CreateApplication();
extern Apex::HeadlessApplication* Apex::CreateHeadlessApplication();

#ifdef AX_HEADLESS
int main(int argc, char** argv)
{
	// Init logger
	Apex::Log::Init();
	AX_CORE_TRACE("Apex Engine initialized in HEADLESS mode.");

	// Create App and run
	auto* App = Apex::CreateHeadlessApplication();
	App->Run();
	delete App;
}
#else
int main(int argc, char** argv)
{
	// Init logger
	Apex::Log::Init();
	AX_CORE_TRACE("Apex Engine initialized in WINDOW mode.");

	// Create App and run
	auto* App = Apex::CreateApplication();
	App->Run();
	delete App;
}
#endif