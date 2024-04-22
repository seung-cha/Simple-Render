#pragma once

#include "RenderUI/RenderUI.h"

#include <iostream>

namespace SimpleRenderUI
{
	class AppMenuUI : public RenderUI
	{
	public:
		AppMenuUI(SimpleRender::RenderApplication* const& application, const std::string& title = "App Menu");

		virtual void UpdateWidget() override;
		
		void ShowMenuWidget();


	};


}