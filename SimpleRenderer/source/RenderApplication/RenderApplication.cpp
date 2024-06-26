
#include "RenderApplication.h"

#include "RenderUI/RenderUI.h"
#include "RenderScene/RenderScene.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "ImGuizmo.h"

#include "RenderUI/BackgroundUI/BackgroundUI.h"
#include "RenderUI/CameraUI/CameraUI.h"
#include "RenderUI/ObjectUI/ObjectUI.h"
#include "RenderUI/ShaderUI/ShaderUI.h"
#include "RenderUI/HierarchyUI/HierarchyUI.h"
#include "RenderUI/ScreenUI/ScreenUI.h"
#include "RenderUI/RenderingUI/RenderingUI.h"
#include "RenderUI/AppMenuUI/AppMenuUI.h"


#include "RenderPure/ContiguousKeyInput.h"
#include "RenderPure/DiscreteKeyInput.h"
#include "RenderPure/MousePositionInput.h"
#include "RenderPure/DiscreteMouseInput.h"

#include "RenderDeferredRender/RenderDeferredRender.h"


#include <iostream>
#include <fstream>
#include "FileReader/FileReader.h"

#include "RenderJson/RenderJson.h"


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


	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// Set up GLFW callback functions
	//


	/// Window Resize Func
	auto resizeFunc = [](GLFWwindow* window, int x, int y)
	{ 
		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));
		app->Status->UpdateWindowSizeStatus(x, y);
	};
	glfwSetFramebufferSizeCallback(window, resizeFunc);





	// Mouse Position Func
	auto mousePosFunc = [](GLFWwindow* window, double x, double y)
	{
		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));
		


		app->Status->Mouse->xPos = static_cast<int>(x);
		app->Status->Mouse->yPos = static_cast<int>(y);

		app->Status->Mouse->deltaXPos = static_cast<int>(app->Status->Mouse->xPos - app->Status->Mouse->lastX);
		app->Status->Mouse->deltaYPos = static_cast<int>(app->Status->Mouse->lastY - app->Status->Mouse->yPos);

		app->Status->Mouse->lastX = app->Status->Mouse->xPos;
		app->Status->Mouse->lastY = app->Status->Mouse->yPos;


		app->Status->Mouse->MouseCoordinates.x = app->Status->Mouse->xPos;
		app->Status->Mouse->MouseCoordinates.y = app->Status->Mouse->yPos;

		app->Status->Mouse->MouseDelta.x = app->Status->Mouse->deltaXPos;
		app->Status->Mouse->MouseDelta.y = app->Status->Mouse->deltaYPos;

		app->Status->Mouse->MouseLastCoordinates.x = app->Status->Mouse->lastX;
		app->Status->Mouse->MouseLastCoordinates.y = app->Status->Mouse->lastY;





		for(auto& input : *app->MousePositionInputs)
		{
			input->OnMousePositionInput(window, x, y);
		}
	};
	glfwSetCursorPosCallback(window, mousePosFunc);




	// Key Func
	auto keyFunc = [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));


		for(auto& input : *app->DiscreteKeyInputs)
		{
			input->OnDiscreteKeyInput(window, key, scancode, action, mods);
		}

	};
	glfwSetKeyCallback(window, keyFunc);



	auto mouseClickFunc = [](GLFWwindow* window, int button, int action, int mods)
	{
		RenderApplication* app = static_cast<RenderApplication*>(glfwGetWindowUserPointer(window));

		app->Status->Mouse->LeftClick = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
		app->Status->Mouse->RightClick = (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);

		for(auto& input : *app->MouseButtonInputs)
		{
			input->OnDiscreteMouseInput(window, button, action, mods);
		}


	};
	glfwSetMouseButtonCallback(window, mouseClickFunc);



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
	AddUI(new ObjectUI(this));
	// AddUI(new CameraUI(this));	// Commented out since it has no use as of now.
	// AddUI(new ShaderUI(this));	// Commented out since it has no use as of now.
	AddUI(new HierarchyUI(this));
	AddUI(new ScreenUI(this));
	AddUI(new RenderingUI(this));
	AddUI(new AppMenuUI(this));



	glEnable(GL_DEPTH_TEST);


}

SimpleRender::RenderApplication::~RenderApplication()
{
	glfwDestroyWindow(window);

	// Manually unregister binds
	// Otherwise they cause access violation
	auto contKeyInputs = contiguousKeyInputs;
	auto discKeyInputs = discreteKeyInputs;
	auto mousePosInputs = mousePositionInputs;
	auto mouseButInputs = mouseButtonInputs;

	for(auto& reg : contKeyInputs)
	{
		reg->UnregisterContiguousKeyInput();
	}

	for(auto& reg : discKeyInputs)
	{
		reg->UnregisterDiscreteKeyInput();
	}

	for(auto& reg : mousePosInputs)
	{
		reg->UnregisterMousePositionInput();
	}

	for(auto& reg : mouseButInputs)
	{
		reg->UnregisterDiscreteMouseInput();
	}

	delete(scene);
}



bool SimpleRender::RenderApplication::Run()
{
	if(!window || !scene || glfwWindowShouldClose(window))
		return false;

	// Update Timer
	status.Time = glfwGetTime();
	status.Timef = static_cast<float>(status.Time);
	status.Timei = static_cast<int>(status.Timef);


	// Do not do anything if the program is in sleep mode (i.e minimised)
	if(status.SleepMode)
	{
		glfwPollEvents();
		return true;
	}

	//Update the screen. Do so so that when no viewports are present the screen keeps refreshing
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	UpdateWidgets();		// Update widget

	ProcessInput();			// Process key inputs


	// Reset the mouse delta values since they don't update unless mouse moves
	status.Mouse->deltaXPos = 0;
	status.Mouse->deltaYPos = 0;
	status.Mouse->MouseDelta.x = 0;
	status.Mouse->MouseDelta.y = 0;


	glfwSwapBuffers(window);
	glfwPollEvents();
	return true;
}

void SimpleRender::RenderApplication::UpdateWidgets()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuizmo::BeginFrame();


	
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
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}




void SimpleRender::RenderApplication::SaveScene()
{
	if(Status->SaveFile.size() <= 0)
	{
		SaveSceneAs();
	}
	else
	{
		json j = scene;
		ofstream of(Status->SaveFile);
		of << j;
		std::cout << j << std::endl;
		of.close();
	}

}

void SimpleRender::RenderApplication::SaveSceneAs()
{
	std::string saveFile = FileReader::OpenSaveFileDialogue();
	
	if(saveFile.size() > 0)
	{
		Status->SaveFile = saveFile;
		SaveScene();
	}

}


void SimpleRender::RenderApplication::LoadScene()
{
	try
	{

		std::string file = FileReader::OpenFileDialogue();

		json json = json::parse(FileReader::ReadFile(file));

		RenderScene* newScene = new RenderScene(this);
	
		if(LoadSceneFromJson(json, newScene))
		{
			delete(scene);
			scene = newScene;
		}
		else
		{
			delete(newScene);
		}

		Status->SaveFile = file;

	}
	catch(std::exception e)
	{
		std::cout << "Unable to load scene: " << e.what() << std::endl;
	}



	

}






void SimpleRender::RenderApplication::ProcessInput()
{
	for(auto& keys : contiguousKeyInputs)
	{
		keys->OnContiguousKeyInput(window);
	}
}



void SimpleRender::RenderApplication::AddUI(RenderUI* const& widget)
{
	widgets.insert(std::unique_ptr<SimpleRenderUI::RenderUI>(widget));
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
	mousePositionInputs.insert(mouseInput);
}

void SimpleRender::RenderApplication::UnregisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput)
{
	mousePositionInputs.erase(mouseInput);
}



void SimpleRender::RenderApplication::RegisterDiscreteMouseInput(SimpleRenderPure::DiscreteMouseInput* mouseInput)
{
	mouseButtonInputs.insert(mouseInput);
}

void SimpleRender::RenderApplication::UnregisterDiscreteMouseInput(SimpleRenderPure::DiscreteMouseInput* mouseInput)
{
	mouseButtonInputs.erase(mouseInput);
}

