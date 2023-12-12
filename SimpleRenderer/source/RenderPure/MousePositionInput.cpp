#include "MousePositionInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::MousePositionInput::MousePositionInput(SimpleRender::RenderApplication* application)
{
	this->application = application;
	RegisterMousePositionInput();

}

SimpleRenderPure::MousePositionInput::~MousePositionInput()
{
	UnregisterMousePositionInput();
}

void SimpleRenderPure::MousePositionInput::RegisterMousePositionInput()
{
	application->RegisterMousePositionInput(this);
}

void SimpleRenderPure::MousePositionInput::UnregisterMousePositionInput()
{
	application->UnregisterMousePositionInput(this);
}
