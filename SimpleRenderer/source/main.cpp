#include "RenderApplication/RenderApplication.h"



int main()
{
	SimpleRender::RenderApplication* application = new SimpleRender::RenderApplication();

	while(application->Run());

	application->Dispose();
}