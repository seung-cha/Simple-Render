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
	registered = true;
}

void SimpleRenderPure::DiscreteKeyInput::UnregisterDiscreteKeyInput()
{
	_application->UnregisterDiscreteKeyInput(this);
	registered = false;
}


SimpleRenderPure::DiscreteKeyInput::~DiscreteKeyInput()
{
	if(registered)
		UnregisterDiscreteKeyInput();
}
