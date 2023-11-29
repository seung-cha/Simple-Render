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

		virtual void UpdateWidget() override;
		

		virtual inline void ReflectUpdate() override
		{

		}

	private:
		void ShadersWidget(enum SimpleRender::ShaderType type);
		void ShaderProgramsWidget();
		void FocusedShaderDetails();
		void FocusedShaderProgramDetails();





	};

}