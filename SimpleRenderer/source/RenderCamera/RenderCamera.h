#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace SimpleRender
{
	class RenderCamera
	{
	public:
		RenderCamera();
		virtual ~RenderCamera() {};
		void Update();


		inline glm::mat4 ViewMatrix() const
		{
			return viewMat;
		}



		inline float FOV() const
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

		inline glm::mat4 PerspectiveMatrix() const
		{
			return perspective;
		}

		inline glm::vec3 Position()
		{
			return position;
		}

	protected:
		glm::mat4 perspective;
		glm::mat4 viewMat;


		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;

		/// <summary>
		/// Update the view matrix with given position and forward vector
		/// </summary>
		inline void CalculateView()
		{
			viewMat = glm::lookAt(position, position + forward, up);
		}


	private:

		float fov = 60.0f;
	};
}