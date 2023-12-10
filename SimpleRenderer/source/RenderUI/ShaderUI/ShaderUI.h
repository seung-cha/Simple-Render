#pragma once
#include "RenderUI/RenderUI.h"


namespace SimpleRenderUI
{
	class ShaderUI : public RenderUI
	{
	public:
		ShaderUI(SimpleRender::RenderScene* scene, std::string title = "Shaders");

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