#include "DiscreteMouseInput.h"
#include "RenderApplication/RenderApplication.h"

SimpleRenderPure::DiscreteMouseInput::DiscreteMouseInput(SimpleRender::RenderApplication* application)
{
	this->_application = application;
	RegisterDiscreteMouseInput();

}

SimpleRenderPure::DiscreteMouseInput::~DiscreteMouseInput()
{
	UnregisterDiscreteMouseInput();
}

void SimpleRenderPure::DiscreteMouseInput::RegisterDiscreteMouseInput()
{
	_application->RegisterDiscreteMouseInput(this);
}

void SimpleRenderPure::DiscreteMouseInput::UnregisterDiscreteMouseInput()
{
	_application->UnregisterDiscreteMouseInput(this);
}
