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

		virtual void UpdateWidget();
		

		virtual inline void ReflectUpdate()
		{

		}

	private:
		void ShadersWidget(enum SimpleRender::ShaderType type);
		void FocusedShaderDetails();
		SimpleRender::RenderShader* selectedShader = nullptr;



	};

}