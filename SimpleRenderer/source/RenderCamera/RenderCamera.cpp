#include "RenderCamera.h"


using namespace SimpleRender;

RenderCamera::RenderCamera()
{
	position = glm::vec3(0.0f, 0.0f, 5.0f);
	target = glm::vec3(0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	SetFOV(90.0f);

	CalculateView();
}


void RenderCamera::Update()
{
	const float rad = 10.0f;
	//float camX = sin(glfwGetTime()) * rad;
	//float camY = cos(glfwGetTime()) * rad;

	//position = glm::vec3(camX, 0.0f, camY);
	CalculateView();
}
