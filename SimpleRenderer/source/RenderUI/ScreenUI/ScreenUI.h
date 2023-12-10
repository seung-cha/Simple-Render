#include "RenderUI/RenderUI.h"



namespace SimpleRenderUI
{
	class ScreenUI : public RenderUI
	{
	public:
		ScreenUI(SimpleRender::RenderScene* scene, std::string title="Scene Screen");
		virtual void UpdateWidget() override;
		virtual void ReflectUpdate() override;


	};

}