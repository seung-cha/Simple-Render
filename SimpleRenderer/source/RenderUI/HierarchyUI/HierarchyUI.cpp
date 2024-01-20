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

		RenderObject* obj = new RenderObject(application->Scene, (*application->Scene->SceneShaderPrograms)[0], application->Scene->SceneObjects->size() + 1, path);
		application->Scene->SceneObjects->push_back(obj);
		application->Scene->ActiveObject = obj;
	}

	for(unsigned int i = 0; i < application->Scene->SceneObjects->size(); i++)
	{
		RenderObject* obj = (*application->Scene->SceneObjects)[i];

		// If the object is a child, do not draw
		if(obj->Parent)
			continue;

		ImGui::PushID(i);


		DrawObjectHierarchy(obj);
		

		ImGui::PopID();
	}



	ImGui::End();

}

void SimpleRenderUI::HierarchyUI::DrawObjectHierarchy(RenderObject* obj)
{
	// If the object has no child, render it as a leaf
	ImGuiTreeNodeFlags flag = obj->Children->size() == 0 ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_None;

	flag |= application->Scene->ActiveObject == obj ? ImGuiTreeNodeFlags_Selected : 0;

	if(ImGui::TreeNodeEx(obj->Name.c_str(), flag))
	{


			// Select object on click
		if(ImGui::IsItemClicked() || ImGui::IsItemToggledOpen())
			application->Scene->ActiveObject = obj;

		for(int i = 0; i < obj->Children->size(); i++)
		{
			DrawObjectHierarchy((*obj->Children)[i]);
		}
		
		ImGui::TreePop();
	}



}
