#include "HierarchyUI.h"
#include <sstream>
#include "FileReader/FileReader.h"
#include "RenderObject/RenderObject.h"


using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;


HierarchyUI::HierarchyUI(RenderScene* scene, string title) : RenderUI(title, scene)
{
	
}

void HierarchyUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	if(ImGui::Button("Add Object"))
	{
		string path = FileReader::OpenFileDialogue();

		RenderObject* obj = new RenderObject(scene, (*scene->SceneShaderPrograms)[0], path);
		scene->SceneObjects->push_back(obj);
		scene->ActiveObject = obj;
	}

	for(unsigned int i = 0; i < scene->SceneObjects->size(); i++)
	{
		ostringstream s;
		s << "Object" << i;

		if(ImGui::Button(s.str().c_str()))
		{
			scene->ActiveObject = (*scene->SceneObjects)[i];
		}


	}



	ImGui::End();

}

