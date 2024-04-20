#pragma once

#include "RenderUI/RenderUI.h"
#include "RenderCamera/RenderCamera.h"

#include <iostream>


namespace SimpleRenderUI
{
	class CameraUI : public RenderUI
	{
	public:
		CameraUI(SimpleRender::RenderApplication* const& application, const std::string& title = "Camera");


		virtual void UpdateWidget() override;
		

		


	};


}