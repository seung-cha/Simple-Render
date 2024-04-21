#include "HierarchyUI.h"
#include <sstream>
#include "FileReader/FileReader.h"
#include "RenderObject/RenderObject.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"

#include <memory>
#include <string>

using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;


HierarchyUI::HierarchyUI(RenderApplication* const& application, const string& title) : RenderUI(title, application)
{
	
}

void HierarchyUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	if(ImGui::Button("Add Object"))
	{
		string path = FileReader::OpenFileDialogue();

		if(path.size() > 0)
		{
			application->Scene->AddObject((*application->Scene->SceneShaderPrograms)[0].get(), path);
			application->Scene->ActiveObject = (*application->Scene->SceneObjects)[application->Scene->SceneObjects->size() - 1].get();
		}

	}

	for(unsigned int i = 0; i < application->Scene->SceneObjects->size(); i++)
	{
		RenderObject* obj = (*application->Scene->SceneObjects)[i].get();

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
	ImGuiTreeNodeFlags flag = obj->Children.size() == 0 ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_None;

	flag |= application->Scene->ActiveObject == obj ? ImGuiTreeNodeFlags_Selected : 0;

	if(ImGui::TreeNodeEx(obj->Name.c_str(), flag))
	{


			// Select object on click
		if(ImGui::IsItemClicked() || ImGui::IsItemToggledOpen())
			application->Scene->ActiveObject = obj;

		for(RenderObject* const& obj : obj->Children)
		{
			DrawObjectHierarchy(obj);
		}
		
		ImGui::TreePop();
	}



}
