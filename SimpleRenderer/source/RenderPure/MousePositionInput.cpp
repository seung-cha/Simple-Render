#include "MousePositionInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::MousePositionInput::MousePositionInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterMousePositionInput();

}

SimpleRenderPure::MousePositionInput::~MousePositionInput()
{
	UnregisterMousePositionInput();
}

void SimpleRenderPure::MousePositionInput::RegisterMousePositionInput()
{
	_application->RegisterMousePositionInput(this);
}

void SimpleRenderPure::MousePositionInput::UnregisterMousePositionInput()
{
	_application->UnregisterMousePositionInput(this);
}
