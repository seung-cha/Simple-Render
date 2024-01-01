#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"
#include "RenderPure/DiscreteMouseInput.h"


#include "RenderBuffer/SelectionBuffer.h"
#include "RenderDeferredRender/RenderDeferredRender.h"


namespace SimpleRenderUI
{



	class ScreenUI : public RenderUI, public SimpleRenderPure::DiscreteMouseInput
	{
	public:
		ScreenUI(SimpleRender::RenderApplication* application, std::string title="Scene Screen");

		virtual void UpdateWidget() override;
		virtual void ReflectUpdate() override;




	private:
		void RenderScene();
		void RenderGizmo();



		SimpleRender::RenderDeferredRender deferredRender;

		// Inherited via DiscreteMouseInput
		virtual void OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods) override;


		GLuint framebuffer;
		GLuint screenTexture;
		GLuint screenRenderbuffer;


		SimpleRenderBuffer::SelectionBuffer selectionBuffer;


		SimpleRender::RenderViewportCamera camera;
		
		bool pressed = false;

	};

}