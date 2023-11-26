#pragma once
#include "RenderUI/RenderUI.h"


namespace SimpleRenderUI
{
	class ShaderUI : public RenderUI
	{
	public:
		ShaderUI(std::string title, SimpleRender::RenderScene* scene) : RenderUI(title, scene)
		{

		}

		virtual inline void UpdateWidget()
		{
			ImGui::Begin(title.c_str()); 


			ImGui::End();
			
		}

		virtual inline void ReflectUpdate()
		{

		}




	};

}