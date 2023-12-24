#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"



namespace SimpleRenderUI
{
	struct SelectionBuffer
	{
		GLuint framebuffer;
		GLuint renderTexture;
		GLuint renderbuffer;
	};



	class ScreenUI : public RenderUI
	{
	public:
		ScreenUI(SimpleRender::RenderApplication* application, std::string title="Scene Screen");

		virtual void UpdateWidget() override;
		virtual void ReflectUpdate() override;


	private:
		void RenderScene();
		void RenderGizmo();
		void InitialiseSelectionBuffer();



		GLuint framebuffer;
		GLuint screenTexture;
		GLuint screenRenderbuffer;

		SelectionBuffer selectionBuffer;

		SimpleRender::RenderViewportCamera camera;
		
	};

}