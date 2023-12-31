#include "RenderUI/RenderUI.h"
#include "RenderCamera/Viewport/RenderViewportCamera.h"
#include "RenderPure/DiscreteMouseInput.h"

// To delete
#include "RenderShaderProgram/RenderShaderProgram.h"

#include "RenderBuffer/SelectionBuffer.h"
#include "RenderBuffer/GBuffer.h"


namespace SimpleRenderUI
{
	struct SelectionBuffer
	{
		GLuint framebuffer;
		GLuint renderTexture;
		GLuint renderbuffer;
	};
	
	struct GBuffer
	{
		GLuint framebuffer;
		GLuint positionTexture;
		GLuint normalTexture;
		GLuint colourTexture;
		GLuint depthTexture;
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



		/* Temp Func to experiment. To be deleted */

		void InitDeferredRender();
		void DeferredRender();

		GLuint deferFramebuffer, deferTexture;
		SimpleRender::RenderShaderProgram deferShaderProgram;
		GLuint deferVAO;
		/* ...................................... */


		// Inherited via DiscreteMouseInput
		virtual void OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods) override;


		GLuint framebuffer;
		GLuint screenTexture;
		GLuint screenRenderbuffer;


		SimpleRenderBuffer::SelectionBuffer selectionBuffer;
		SimpleRenderBuffer::GBuffer gBuffer;


		SimpleRender::RenderViewportCamera camera;
		
		bool pressed = false;

	};

}