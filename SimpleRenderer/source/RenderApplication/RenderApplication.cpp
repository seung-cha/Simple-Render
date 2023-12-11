#include "RenderApplication.h"

#include "RenderUI/RenderUI.h"
#include "RenderScene/RenderScene.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"



#include "RenderUI/BackgroundUI/BackgroundUI.h"
#include "RenderUI/CameraUI/CameraUI.h"
#include "RenderUI/ObjectUI/ObjectUI.h"
#include "RenderUI/ShaderUI/ShaderUI.h"
#include "RenderUI/HierarchyUI/HierarchyUI.h"
#include "RenderUI/ScreenUI/ScreenUI.h"


#include <iostream>
#include <functional>


using namespace SimpleRender;
using namespace SimpleRenderUI;
using namespace std;


RenderApplication::RenderApplication()
{


	// Initialise GLAD
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(status.Width, status.Height, status.Title.c_str(), 0, 0);
	
	if(!window)
	{
		std::cout << "An error occurred" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	//Set up callbacks
	glfwSetWindowUserPointer(window, this);


	auto resizeFunc = [](GLFWwindow* window, int x, int y)
	{ 
		cout << x << ", " << y << endl;
		static_cast<RenderApplication*>(glfwGetWindowUserPointer(window))->Status->UpdateWindowSizeStatus(x, y);
	};
	glfwSetFramebufferSizeCallback(window, resizeFunc);


	auto keyFunc = [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	};
	glfwSetKeyCallback(window, keyFunc);





	// Load Scene
	scene = new RenderScene(this);
	scene->LoadDefaultScene();



	// Initialise ImGUI and UI widgets
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");


	// Add Widgets
	AddUI(new BackgroundUI(scene));
	AddUI(new CameraUI(scene));
	AddUI(new ObjectUI(scene));
	AddUI(new ShaderUI(scene));
	AddUI(new HierarchyUI(scene));
	AddUI(new ScreenUI(scene));

	glEnable(GL_DEPTH_TEST);


}



bool RenderApplication::Run()
{
	if(!window || !scene || glfwWindowShouldClose(window))
		return false;

	// Do not do anything if the program is in sleep mode (i.e minimised)
	if(status.SleepMode)
	{
		glfwPollEvents();
		return true;
	}

	scene->DrawScene();
	
	UpdateWidgets();

	glfwSwapBuffers(window);
	glfwPollEvents();
	return true;
}

void RenderApplication::UpdateWidgets()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	
	const ImGuiViewport* v = ImGui::GetMainViewport();

	ImGui::SetNextWindowSize(v->WorkSize);
	ImGui::SetNextWindowPos(v->WorkPos);
	ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImGuiID id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(id);

	ImGui::End();
	

	for(auto& widget : widgets)
	{
		widget->UpdateWidget();
		widget->ReflectUpdate();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void RenderApplication::AddUI(RenderUI* widget)
{
	widgets.insert(widget);
}



void RenderApplication::Dispose()
{
	glfwTerminate();

	for(auto& widget : widgets)
	{
		delete(widget);
	}

	scene->Dispose();
	delete(scene);



}