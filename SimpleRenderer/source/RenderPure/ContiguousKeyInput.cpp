#include "ContiguousKeyInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::ContiguousKeyInput::ContiguousKeyInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterContiguousKeyInput();
}


SimpleRenderPure::ContiguousKeyInput::~ContiguousKeyInput()
{
	if(registered)
		_application->UnregisterContiguousKeyInput(this);
}

void SimpleRenderPure::ContiguousKeyInput::RegisterContiguousKeyInput()
{
	_application->RegisterContiguousKeyInput(this);
	registered = true;
}

void SimpleRenderPure::ContiguousKeyInput::UnregisterContiguousKeyInput()
{
	_application->UnregisterContiguousKeyInput(this);
	registered = false;
}