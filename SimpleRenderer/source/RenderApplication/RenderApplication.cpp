#include "RenderApplication.h"
#include <iostream>


using namespace SimpleRender;


RenderApplication::RenderApplication()
{
	// Initialise GLAD
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(width, height, title.c_str(), 0, 0);
	
	if(!window)
	{
		std::cout << "An error occurred" << std::endl;
		glfwTerminate();
		return;
	}



	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	


}



bool RenderApplication::Run()
{
	if(!window || !scene)
		return false;

	scene->DrawScene();



	glfwSwapBuffers(window);
	glfwPollEvents();
	return true;
}


template<typename T>
void RenderApplication::AddUI(T widget)
{


}