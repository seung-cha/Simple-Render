#pragma once

#include "RenderUI/RenderUI.h"



namespace SimpleRenderUI
{
	class RenderingUI : public RenderUI
	{
	public:
		RenderingUI(SimpleRender::RenderApplication* application, std::string title = "Rendering");


		void UpdateWidget() override;
		void ReflectUpdate() override;


	};



}