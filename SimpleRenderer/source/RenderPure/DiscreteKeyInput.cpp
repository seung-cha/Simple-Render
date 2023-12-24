#include "DiscreteKeyInput.h"
#include "RenderApplication/RenderApplication.h"



SimpleRenderPure::DiscreteKeyInput::DiscreteKeyInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterDiscreteKeyInput();
}


void SimpleRenderPure::DiscreteKeyInput::RegisterDiscreteKeyInput()
{
	_application->RegisterDiscreteKeyInput(this);
}

void SimpleRenderPure::DiscreteKeyInput::UnregisterDiscreteKeyInput()
{
	_application->UnregisterDiscreteKeyInput(this);
}


SimpleRenderPure::DiscreteKeyInput::~DiscreteKeyInput()
{
	UnregisterDiscreteKeyInput();
}
