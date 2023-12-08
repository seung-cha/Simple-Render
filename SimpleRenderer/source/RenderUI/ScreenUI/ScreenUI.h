#include "RenderUI/RenderUI.h"



namespace SimpleRenderUI
{
	class ScreenUI : public RenderUI
	{
	public:
		ScreenUI(std::string title, SimpleRender::RenderScene* scene);
		virtual void UpdateWidget() override;
		virtual void ReflectUpdate() override;


	};

}