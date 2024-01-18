#include "HierarchyUI.h"
#include <sstream>
#include "FileReader/FileReader.h"
#include "RenderObject/RenderObject.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"

#include <string>

using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;


HierarchyUI::HierarchyUI(RenderApplication* application, string title) : RenderUI(title, application)
{
	
}

void HierarchyUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	if(ImGui::Button("Add Object"))
	{
		string path = FileReader::OpenFileDialogue();

		RenderObject* obj = new RenderObject(application->Scene, (*application->Scene->SceneShaderPrograms)[0], (*application->Scene->SceneObjects).size() + 1, path);
		application->Scene->SceneObjects->push_back(obj);
		application->Scene->ActiveObject = obj;
	}

	for(unsigned int i = 0; i < application->Scene->SceneObjects->size(); i++)
	{
		string s;
		

		if((*application->Scene->SceneObjects)[i]->Name == "")
			s = "Object";
		else
			s = (*application->Scene->SceneObjects)[i]->Name;


		ImGui::PushID(i);

		if(ImGui::Button(s.c_str()))
		{
			application->Scene->ActiveObject = (*application->Scene->SceneObjects)[i];
		}

		ImGui::PopID();


	}



	ImGui::End();

}

