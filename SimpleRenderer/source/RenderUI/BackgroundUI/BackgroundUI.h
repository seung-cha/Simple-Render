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

		virtual void UpdateWidget();

		virtual inline void ReflectUpdate()
		{
			glClearColor(background.r, background.g, background.b, 1.0f);
		}

	private:
		glm::vec3 background;
		unsigned int colourFlags;


	};

}