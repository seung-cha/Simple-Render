#pragma once

#include "RenderUI/RenderUI.h"



#include <iostream>
namespace SimpleRenderUI
{
	class BackgroundUI : public RenderUI
	{
	public:
		BackgroundUI(SimpleRender::RenderApplication* const& application, const std::string& title = "Background");


		virtual void UpdateWidget() override;



	};

}