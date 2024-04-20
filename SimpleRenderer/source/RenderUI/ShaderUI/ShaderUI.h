#pragma once
#include "RenderUI/RenderUI.h"


namespace SimpleRender
{
	enum ShaderType;
}

namespace SimpleRenderUI
{
	enum SimpleRender::ShaderType;

	class ShaderUI : public RenderUI
	{
	public:
		ShaderUI(SimpleRender::RenderApplication* const& application, const std::string& title = "Shaders");

		virtual void UpdateWidget() override;
		

	private:
		void ShadersWidget(enum SimpleRender::ShaderType type);
		void ShaderProgramsWidget();
		void FocusedShaderDetails();
		void FocusedShaderProgramDetails();





	};

}