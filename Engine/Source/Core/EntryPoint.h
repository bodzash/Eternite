#pragma once

extern Apex::Application* Apex::CreateApplication();
extern Apex::HeadlessApp* Apex::CreateHeadlessApp();

#ifdef AX_HEADLESS
int main(int argc, char** argv)
{
	// Init logger
	Apex::Log::Init();
	AX_CORE_TRACE("Apex Engine initialized in HEADLESS mode.");

	// Create App and run
	auto* App = Apex::CreateHeadlessApp();
	App->Run();
	delete App;
}
#else
int main(int argc, char** argv)
{
	// Init logger
	Apex::Log::Init();
	AX_CORE_TRACE("Apex Engine initialized in GRAPHICAL mode.");

	// Create App and run
	auto* App = Apex::CreateApplication();
	App->Run();
	delete App;
}
#endif