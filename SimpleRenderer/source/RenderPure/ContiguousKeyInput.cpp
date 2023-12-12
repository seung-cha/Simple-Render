#include "ContiguousKeyInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::ContiguousKeyInput::ContiguousKeyInput(SimpleRender::RenderApplication* application)
{
	this->application = application;
	RegisterContiguousKeyInput();
}


SimpleRenderPure::ContiguousKeyInput::~ContiguousKeyInput()
{
	application->UnregisterContiguousKeyInput(this);
}

void SimpleRenderPure::ContiguousKeyInput::RegisterContiguousKeyInput()
{
	application->RegisterContiguousKeyInput(this);
}

void SimpleRenderPure::ContiguousKeyInput::UnregisterContiguousKeyInput()
{
	application->UnregisterContiguousKeyInput(this);
}