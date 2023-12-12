#pragma once

struct GLFWwindow;

namespace SimpleRender
{
	class RenderApplication;
}


namespace SimpleRenderPure
{
	/// <summary>
	/// Interface to receive discrete key input
	/// Pass a reference to an application
	/// 
	/// Automatically registers for input when created.
	/// </summary>
	class DiscreteKeyInput
	{
	public:
		DiscreteKeyInput(SimpleRender::RenderApplication* application);
		virtual ~DiscreteKeyInput();

		void RegisterDiscreteKeyInput();
		void UnregisterDiscreteKeyInput();
		

		virtual void OnDiscreteKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;


	private:
		SimpleRender::RenderApplication* application;


	};


}