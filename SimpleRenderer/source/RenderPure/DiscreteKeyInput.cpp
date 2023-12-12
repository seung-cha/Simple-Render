#include "DiscreteKeyInput.h"
#include "RenderApplication/RenderApplication.h"



SimpleRenderPure::DiscreteKeyInput::DiscreteKeyInput(SimpleRender::RenderApplication* application)
{
	this->application = application;
	RegisterDiscreteKeyInput();
}


void SimpleRenderPure::DiscreteKeyInput::RegisterDiscreteKeyInput()
{
	application->RegisterDiscreteKeyInput(this);
}

void SimpleRenderPure::DiscreteKeyInput::UnregisterDiscreteKeyInput()
{
	application->UnregisterDiscreteKeyInput(this);
}


SimpleRenderPure::DiscreteKeyInput::~DiscreteKeyInput()
{
	UnregisterDiscreteKeyInput();
}
