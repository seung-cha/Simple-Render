#include "BackgroundUI.h"



using namespace SimpleRenderUI;


void BackgroundUI::UpdateWidget()
{

	ImGui::Begin(title.c_str());
	ImGui::ColorPicker3("Background Colour", &background[0]);
	ImGui::End();
}
