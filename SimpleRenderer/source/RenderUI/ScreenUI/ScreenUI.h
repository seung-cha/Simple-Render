#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"
#include "RenderPure/DiscreteMouseInput.h"


#include "RenderBuffer/RenderBuffer.h"
#include "RenderBuffer/SelectionBuffer.h"


namespace SimpleRenderUI
{



	class ScreenUI : public RenderUI, public SimpleRenderPure::DiscreteMouseInput, public SimpleRenderPure::DiscreteKeyInput
	{
	public:
		ScreenUI(SimpleRender::RenderApplication* const& application, const std::string& title ="Scene Screen");

		virtual void UpdateWidget() override;




	private:
		void RenderScene();
		void RenderGizmo();

		// Inherited via DiscreteMouseInput
		virtual void OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods) override;

		// Inherited via DiscreteKeyInput
		virtual void OnDiscreteKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) override;
		


		GLuint framebuffer;
		GLuint screenTexture;
		GLuint screenRenderbuffer;


		SimpleRenderBuffer::SelectionBuffer selectionBuffer;
		SimpleRenderBuffer::DeferBuffer deferBuffer;



		SimpleRender::RenderViewportCamera camera;
		
		bool pressed = false;
		bool showSelectBuffer = false;
		int lastID = -1;




	};

}