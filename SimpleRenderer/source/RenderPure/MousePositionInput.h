#pragma once

struct GLFWwindow;

namespace SimpleRender
{
	class RenderApplication;

}

namespace SimpleRenderPure
{
	class MousePositionInput
	{
	public:
		MousePositionInput(SimpleRender::RenderApplication* application);
		virtual ~MousePositionInput();


		void RegisterMousePositionInput();
		void UnregisterMousePositionInput();


		virtual void OnMousePositionInput(GLFWwindow* window, double x, double y) = 0;

	private:
		SimpleRender::RenderApplication* application;



	};




}