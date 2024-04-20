#include "DiscreteMouseInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::DiscreteMouseInput::DiscreteMouseInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterDiscreteMouseInput();

}

SimpleRenderPure::DiscreteMouseInput::~DiscreteMouseInput()
{
	if(registered)
		UnregisterDiscreteMouseInput();
}

void SimpleRenderPure::DiscreteMouseInput::RegisterDiscreteMouseInput()
{
	_application->RegisterDiscreteMouseInput(this);
	registered = true;
}

void SimpleRenderPure::DiscreteMouseInput::UnregisterDiscreteMouseInput()
{
	_application->UnregisterDiscreteMouseInput(this);
	registered = false;
}
