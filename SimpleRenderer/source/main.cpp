#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "FileReader/FileReader.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "RenderScene/RenderScene.h"

#include "RenderUI/BackgroundUI/BackgroundUI.h"
#include "RenderUI/CameraUI/CameraUI.h"
#include "RenderUI/ObjectUI/ObjectUI.h"
#include "RenderUI/ShaderUI/ShaderUI.h"
#include "RenderUI/HierarchyUI/HierarchyUI.h"
#include "RenderUI/ScreenUI/ScreenUI.h"
#include "RenderApplication/RenderApplication.h"



int main()
{
	SimpleRender::RenderApplication* application = new SimpleRender::RenderApplication();


	while(application->Run());

	
	application->Dispose();
}

SimpleRender::RenderScene* scene;
/*
int main()
{
	int width = 1920;
	int height = 1080;
	std::string title = "Simple Renderer";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);


	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), 0, 0);

	if(!window)
	{
		std::cout << "An error occurred" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, OnWindowResized);
	glfwSetKeyCallback(window, OnKeyPressed);
	glfwSetCursorPosCallback(window, OnMousePosChanged);



	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, width, height);

	
	GLuint program, fragShader, vertShader;

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	vertShader = glCreateShader(GL_VERTEX_SHADER);

	program = glCreateProgram(); 

	const char* fragSource;
	const char* vertSource;

	vertSource = FileReader::ReadFile("shaders/debug/debug.vert");
	fragSource = FileReader::ReadFile("shaders/debug/debug.frag");


	glShaderSource(fragShader, 1, &fragSource, 0);
	glShaderSource(vertShader, 1, &vertSource, 0);

	glCompileShader(fragShader);
	glCompileShader(vertShader);

	glAttachShader(program, fragShader);
	glAttachShader(program, vertShader);

	glLinkProgram(program);

	glDeleteShader(fragShader);
	glDeleteShader(vertShader);

	free((void*)fragSource);
	free((void*)vertSource);

	glEnable(GL_DEPTH_TEST);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Scene
	scene = new SimpleRender::RenderScene(width, height);
	scene->LoadDefaultScene();

	// UI widgets
	std::vector<SimpleRenderUI::RenderUI*> renderUIs;
	renderUIs.push_back(new SimpleRenderUI::BackgroundUI(scene));
	renderUIs.push_back(new SimpleRenderUI::CameraUI(scene));
	renderUIs.push_back(new SimpleRenderUI::ObjectUI(scene));
	renderUIs.push_back(new SimpleRenderUI::ShaderUI(scene));
	renderUIs.push_back(new SimpleRenderUI::HierarchyUI(scene));
	renderUIs.push_back(new SimpleRenderUI::ScreenUI(scene));



	while(!glfwWindowShouldClose(window))
	{

		// Quit window
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);



		scene->DrawScene();

		scene->ActiveCamera->Update();
		scene->ActiveCamera->Input(window);

		//glfwGetWindowAttrib(window,GLFW_MINI )

	

		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		const ImGuiViewport* v = ImGui::GetMainViewport();

		ImGui::SetNextWindowSize(v->WorkSize);
		ImGui::SetNextWindowPos(v->WorkPos);

		ImGui::Begin("Window", 0, ImGuiWindowFlags_NoTitleBar);

		ImGuiID id = ImGui::GetID("DockSpace");
		ImGui::DockSpace(id);

		ImGui::End();

		// Draw UIs
		for(auto& ui : renderUIs)
		{
			ui->UpdateWidget();
			ui->ReflectUpdate();
		}

		


		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// Retarget the current context to this. IMGUI changes context in docking mode
			GLFWwindow* thisWindow = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(thisWindow);
			
		}

	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	// Free UIs
	for(auto& ui : renderUIs)
	{
		delete(ui);
	}

	scene->Dispose();
	delete(scene);


	std::cout << "Hello World!!" << std::endl;
	return 0; 

}
*/


