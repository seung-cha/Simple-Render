#include "RenderCamera.h"

#include <iostream>

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
	CalculateView();
}




