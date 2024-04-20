#include "RenderApplication/RenderApplication.h"
#include <memory>


int main()
{
	std::unique_ptr<SimpleRender::RenderApplication> application = std::make_unique<SimpleRender::RenderApplication>();
	while(application->Run());


}