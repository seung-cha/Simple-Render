#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"
#include "RenderPure/DiscreteMouseInput.h"


#include "RenderBuffer/RenderBuffer.h"
#include "RenderBuffer/SelectionBuffer.h"


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

		// Inherited via DiscreteMouseInput
		virtual void OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods) override;


		GLuint framebuffer;
		GLuint screenTexture;
		GLuint screenRenderbuffer;


		SimpleRenderBuffer::SelectionBuffer selectionBuffer;
		SimpleRenderBuffer::DeferBuffer deferBuffer;



		SimpleRender::RenderViewportCamera camera;
		
		bool pressed = false;

	};

}