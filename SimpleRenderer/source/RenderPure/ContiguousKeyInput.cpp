#include "ContiguousKeyInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::ContiguousKeyInput::ContiguousKeyInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterContiguousKeyInput();
}


SimpleRenderPure::ContiguousKeyInput::~ContiguousKeyInput()
{
	_application->UnregisterContiguousKeyInput(this);
}

void SimpleRenderPure::ContiguousKeyInput::RegisterContiguousKeyInput()
{
	_application->RegisterContiguousKeyInput(this);
}

void SimpleRenderPure::ContiguousKeyInput::UnregisterContiguousKeyInput()
{
	_application->UnregisterContiguousKeyInput(this);
}