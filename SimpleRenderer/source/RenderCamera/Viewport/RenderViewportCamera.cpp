#include "RenderViewportCamera.h"

#include <iostream>

SimpleRender::RenderViewportCamera::RenderViewportCamera(RenderApplication* application) : RenderCamera(),
ContiguousKeyInput(application), DiscreteKeyInput(application), MousePositionInput(application)
{

	

}



void SimpleRender::RenderViewportCamera::OnContiguousKeyInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * forward;
	}

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -forward;

	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -right;

	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * right;

	}
}

void SimpleRender::RenderViewportCamera::OnDiscreteKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_C && action == GLFW_PRESS)
	{

		ToggleFocus(window);
	}
}

void SimpleRender::RenderViewportCamera::OnMousePositionInput(GLFWwindow* window, double x, double y)
{
	if(focused)
	{
		float dX = static_cast<float>(x - lastX);
		// Reverse Y coords since it's from bottom to top
		float dY = static_cast<float>(lastY - y);

		dX *= sens;
		dY *= sens;

		yaw += dX;
		pitch += dY;


		if(pitch > 89.0f)
			pitch = 89.0f;
		else if(pitch < -89.0f)
			pitch = -89.0f;


		// Calculate new forward
		glm::vec3 newFor;
		newFor.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newFor.y = sin(glm::radians(pitch));
		newFor.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		forward = glm::normalize(newFor);
		right = glm::cross(forward, up);

	}

	lastX = x;
	lastY = y;
}

void SimpleRender::RenderViewportCamera::ToggleFocus(GLFWwindow* window)
{
	focused = !focused;

	if(focused)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}