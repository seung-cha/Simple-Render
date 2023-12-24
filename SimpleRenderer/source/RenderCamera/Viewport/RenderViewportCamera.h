#include "RenderCamera/RenderCamera.h"
#include "RenderPure/ContiguousKeyInput.h"
#include "RenderPure/DiscreteKeyInput.h"
#include "RenderPure/MousePositionInput.h"


namespace SimpleRender
{
	class RenderApplication;


	class RenderViewportCamera : public RenderCamera, public SimpleRenderPure::ContiguousKeyInput,
		public SimpleRenderPure::DiscreteKeyInput, public SimpleRenderPure::MousePositionInput
	{
	public:
		RenderViewportCamera(RenderApplication* application);


		/// <summary>
		/// Should the camera receive input and update its posiiton?
		/// </summary>
		bool Active = false;

	private:
		void ToggleFocus(GLFWwindow* window);

		float speed = 1.5f;
		float sens = 0.1f;

		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = -90.0f;

		bool focused = false;

		double lastX = 0;
		double lastY = 0;


		// Inherited via ContiguousKeyInput
		virtual void OnContiguousKeyInput(GLFWwindow* window) override;
		virtual void OnDiscreteKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) override;
		virtual void OnMousePositionInput(GLFWwindow* window, double x, double y) override;

	};




}



