#include "RenderCamera/RenderCamera.h"




namespace SimpleRender
{
	class RenderViewportCamera : public RenderCamera
	{
	public:
		RenderViewportCamera();



	private:

		float speed = 1.5f;
		float sens = 0.1f;
		float fov = 60.0f;

		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = -90.0f;

		bool focused = false;

		double lastX = 0;
		double lastY = 0;


	};




}



