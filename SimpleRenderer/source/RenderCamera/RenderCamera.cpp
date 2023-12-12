#include "RenderCamera.h"

#include <GLFW/glfw3.h>
#include <iostream>

using namespace SimpleRender;



RenderCamera::RenderCamera()
{
	position = glm::vec3(0.0f, 0.0f, 5.0f);
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::cross(forward, up);


	SetFOV(60.0f);
	CalculateView();



}


void RenderCamera::Update()
{
	CalculateView();
}




