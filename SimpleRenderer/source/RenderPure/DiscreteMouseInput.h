#pragma once

struct GLFWwindow;

namespace SimpleRender
{
	class RenderApplication;
}

namespace SimpleRenderPure
{

	class DiscreteMouseInput
	{
	public:
		DiscreteMouseInput(SimpleRender::RenderApplication* application);
		virtual ~DiscreteMouseInput();

		void RegisterDiscreteMouseInput();
		void UnregisterDiscreteMouseInput();

		virtual void OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods) = 0;


	private:
		
		SimpleRender::RenderApplication* _application;

	};


}