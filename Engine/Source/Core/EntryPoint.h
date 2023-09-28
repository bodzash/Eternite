#pragma once

#ifdef AX_PLATFORM_WINDOWS

extern Apex::Application* Apex::CreateApplication();

int main(int argc, char** argv)
{
	// Init logger
	Apex::Log::Init();
	AX_CORE_TRACE("Apex Engine initialized.");

	// Create App and run
	auto* App = Apex::CreateApplication();
	App->Run();
	delete App;
}

#endif