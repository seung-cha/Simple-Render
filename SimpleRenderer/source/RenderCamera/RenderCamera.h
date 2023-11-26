#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>



namespace SimpleRender
{
	class RenderCamera
	{
	public:
		RenderCamera();
		void Update();

		inline glm::mat4 ViewMatrix()
		{
			return viewMat;
		}



		inline float FOV()
		{
			return fov;
		}

		inline void SetFOV(float fov)
		{
			this->fov = fov;

			int width, height;
			glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
			perspective = glm::perspective(glm::radians(fov), width / (float)height, 0.1f, 1000.0f);
		}

		inline glm::mat4 Perspective()
		{
			return perspective;
		}

	private:
		inline void CalculateView()
		{
			viewMat = glm::lookAt(position, target, up);
		}

		float fov;
		glm::mat4 perspective;
		glm::mat4 viewMat;
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 up;

	};
}