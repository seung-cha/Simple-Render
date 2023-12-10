#pragma once

#include "RenderUI/RenderUI.h"
#include "RenderCamera/RenderCamera.h"

#include <iostream>


namespace SimpleRenderUI
{
	class CameraUI : public RenderUI
	{
	public:
		CameraUI(SimpleRender::RenderScene* scene, std::string title = "Camera");


		virtual void UpdateWidget() override;
		

		virtual inline void ReflectUpdate() override
		{
			cam->SetFOV(fov);

		}

	private:
		float fov;
		SimpleRender::RenderCamera* cam;
		


	};


}