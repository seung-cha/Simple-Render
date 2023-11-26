#pragma once

#include "RenderUI/RenderUI.h"



#include <iostream>
namespace SimpleRenderUI
{
	class BackgroundUI : public RenderUI
	{
	public:
		inline BackgroundUI(std::string title, SimpleRender::RenderScene* scene) : RenderUI(title, scene)
		{
			background = glm::vec3(0.54f, 0.7f, 0.12f);

			colourFlags = 0;

		}

		virtual inline void UpdateWidget()
		{
			
			ImGui::Begin(title.c_str());
			ImGui::ColorPicker3("Background Colour", &background[0]);
			ImGui::End();
		}

		virtual inline void ReflectUpdate()
		{
			glClearColor(background.r, background.g, background.b, 1.0f);
		}

	private:
		glm::vec3 background;
		unsigned int colourFlags;


	};

}