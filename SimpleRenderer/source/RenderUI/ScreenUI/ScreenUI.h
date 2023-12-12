#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"



namespace SimpleRenderUI
{
	class ScreenUI : public RenderUI
	{
	public:
		ScreenUI(SimpleRender::RenderApplication* application, std::string title="Scene Screen");

		virtual void UpdateWidget() override;
		virtual void ReflectUpdate() override;


	private:
		void RenderScene();


		GLuint framebuffer;
		GLuint texture;

		SimpleRender::RenderViewportCamera camera;
		
	};

}