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

#include "RenderPure/ContiguousKeyInput.h"
#include "RenderPure/DiscreteKeyInput.h"
#include "RenderPure/MousePositionInput.h"


#include <iostream>
#include <functional>


using namespace SimpleRender;
using namespace SimpleRenderUI;
using namespace std;


SimpleRender::RenderApplication::RenderApplication()
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
		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));
		app->Status->UpdateWindowSizeStatus(x, y);
	};
	glfwSetFramebufferSizeCallback(window, resizeFunc);


	auto mousePosFunc = [](GLFWwindow* window, double x, double y)
	{
		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));

		for(auto& input : *app->MousePositionInputs)
		{
			input->OnMousePositionInput(x, y);
		}
	};

	glfwSetCursorPosCallback(window, mousePosFunc);


	auto keyFunc = [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));


		for(auto& input : *app->DiscreteKeyInputs)
		{
			input->OnDiscreteKeyInput(key, scancode, action, mods);
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
	AddUI(new BackgroundUI(this));
	AddUI(new CameraUI(this));
	AddUI(new ObjectUI(this));
	AddUI(new ShaderUI(this));
	AddUI(new HierarchyUI(this));
	AddUI(new ScreenUI(this));

	glEnable(GL_DEPTH_TEST);


}



bool SimpleRender::RenderApplication::Run()
{
	if(!window || !scene || glfwWindowShouldClose(window))
		return false;

	// Do not do anything if the program is in sleep mode (i.e minimised)
	if(status.SleepMode)
	{
		glfwPollEvents();
		return true;
	}


	scene->DrawScene();		// Draw Scene (Will be removed)
	
	UpdateWidgets();		// Update widget

	ProcessInput();			// Process key inputs

	glfwSwapBuffers(window);
	glfwPollEvents();
	return true;
}

void SimpleRender::RenderApplication::UpdateWidgets()
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

void SimpleRender::RenderApplication::ProcessInput()
{
	for(auto& keys : contiguousKeyInputs)
	{
		keys->OnContiguousKeyInput();
	}


}



void SimpleRender::RenderApplication::AddUI(RenderUI* widget)
{
	widgets.insert(widget);
}


void SimpleRender::RenderApplication::Dispose()
{
	glfwTerminate();

	for(auto& widget : widgets)
	{
		delete(widget);
	}

	scene->Dispose();
	delete(scene);

}

void SimpleRender::RenderApplication::RegisterContiguousKeyInput(SimpleRenderPure::ContiguousKeyInput* keyInput)
{
	contiguousKeyInputs.insert(keyInput);
}

void SimpleRender::RenderApplication::UnregisterContiguousKeyInput(SimpleRenderPure::ContiguousKeyInput* keyInput)
{
	contiguousKeyInputs.erase(keyInput);
}



void SimpleRender::RenderApplication::RegisterDiscreteKeyInput(SimpleRenderPure::DiscreteKeyInput* keyInput)
{
	discreteKeyInputs.insert(keyInput);
}



void SimpleRender::RenderApplication::UnregisterDiscreteKeyInput(SimpleRenderPure::DiscreteKeyInput* keyInput)
{
	discreteKeyInputs.erase(keyInput);
}

void SimpleRender::RenderApplication::RegisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput)
{
	mousePositionInput.insert(mouseInput);
}

void SimpleRender::RenderApplication::UnregisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput)
{
	mousePositionInput.erase(mouseInput);

}