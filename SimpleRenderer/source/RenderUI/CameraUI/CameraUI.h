#pragma once

#include "RenderUI/RenderUI.h"
#include "RenderCamera/RenderCamera.h"

#include <iostream>


namespace SimpleRenderUI
{
	class CameraUI : public RenderUI
	{
	public:
		inline CameraUI(std::string title, SimpleRender::RenderScene* scene) : RenderUI(title, scene)
		{
			this->cam = scene->ActiveCamera;
			fov = cam->FOV();
		}

		virtual void UpdateWidget();
		

		virtual inline void ReflectUpdate()
		{
			cam->SetFOV(fov);

		}

	private:
		float fov;
		SimpleRender::RenderCamera* cam;
		


	};


}