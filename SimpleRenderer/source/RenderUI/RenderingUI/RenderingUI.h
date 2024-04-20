#pragma once

#include "RenderUI/RenderUI.h"



namespace SimpleRenderUI
{
	class RenderingUI : public RenderUI
	{
	public:
		RenderingUI(SimpleRender::RenderApplication* const& application, const std::string& title = "Rendering");


		void UpdateWidget() override;



	};



}