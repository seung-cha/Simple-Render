#include "RenderViewportCamera.h"

#include <iostream>

SimpleRender::RenderViewportCamera::RenderViewportCamera(RenderApplication* application) : RenderCamera(),
ContiguousKeyInput(application), DiscreteKeyInput(application), MousePositionInput(application)
{

	

}



void SimpleRender::RenderViewportCamera::OnContiguousKeyInput()
{

}

void SimpleRender::RenderViewportCamera::OnDiscreteKeyInput(int key, int scancode, int action, int mods)
{

}

void SimpleRender::RenderViewportCamera::OnMousePositionInput(double x, double y)
{


}