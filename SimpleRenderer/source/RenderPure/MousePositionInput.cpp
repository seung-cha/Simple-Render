#include "MousePositionInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::MousePositionInput::MousePositionInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterMousePositionInput();

}

SimpleRenderPure::MousePositionInput::~MousePositionInput()
{
	if(registered)
		UnregisterMousePositionInput();
}

void SimpleRenderPure::MousePositionInput::RegisterMousePositionInput()
{
	_application->RegisterMousePositionInput(this);
	registered = true;
}

void SimpleRenderPure::MousePositionInput::UnregisterMousePositionInput()
{
	_application->UnregisterMousePositionInput(this);
	registered = false;
}
