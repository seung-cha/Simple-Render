#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"
#include "RenderPure/DiscreteMouseInput.h"



namespace SimpleRenderUI
{
	struct SelectionBuffer
	{
		GLuint framebuffer;
		GLuint renderTexture;
		GLuint renderbuffer;
	};



	class ScreenUI : public RenderUI, public SimpleRenderPure::DiscreteMouseInput
	{
	public:
		ScreenUI(SimpleRender::RenderApplication* application, std::string title="Scene Screen");

		virtual void UpdateWidget() override;
		virtual void ReflectUpdate() override;




	private:
		void RenderScene();
		void RenderGizmo();
		void InitialiseSelectionBuffer();

		// Inherited via DiscreteMouseInput
		virtual void OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods) override;


		GLuint framebuffer;
		GLuint screenTexture;
		GLuint screenRenderbuffer;

		SelectionBuffer selectionBuffer;

		SimpleRender::RenderViewportCamera camera;
		
		bool pressed = false;

	};

}