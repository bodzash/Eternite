#include <Apex.h>
#include <ApexEntryPoint.h>
#include <filesystem>
#include "EditorLayer.h"

using namespace Apex;

class GameEditor : public Application
{
public:
	GameEditor()
	{
		PushLayer(new EditorLayer());
	}
};

Apex::Application* Apex::CreateApplication()
{
	// TODO: ONLY PRESENT IN INTERNAL BUILD, NOT IN DIST
	auto path = std::filesystem::current_path().parent_path().parent_path().parent_path();
	std::filesystem::current_path(path);
	AX_INFO("Path changed: {0}", path);

	return new GameEditor();
}