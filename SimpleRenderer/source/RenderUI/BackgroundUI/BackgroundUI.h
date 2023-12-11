#pragma once

#include "RenderUI/RenderUI.h"



#include <iostream>
namespace SimpleRenderUI
{
	class BackgroundUI : public RenderUI
	{
	public:
		BackgroundUI(SimpleRender::RenderApplication* application, std::string title = "Background");


		virtual void UpdateWidget() override;

		virtual inline void ReflectUpdate() override
		{
			glClearColor(background.r, background.g, background.b, 1.0f);
		}

	private:
		glm::vec3 background;
		unsigned int colourFlags;


	};

}