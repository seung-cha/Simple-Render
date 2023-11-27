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



void OnWindowResized(GLFWwindow* window, int width, int height);


int main()
{

	int width = 1920;
	int height = 1080;
	std::string title = "Simple Renderer";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	
	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), 0, 0);

	if(!window)
	{
		std::cout << "An error occurred" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, OnWindowResized);


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
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Scene
	SimpleRender::RenderScene scene;
	scene.LoadDefaultScene();

	// UI widgets
	std::vector<SimpleRenderUI::RenderUI*> renderUIs;
	renderUIs.push_back(new SimpleRenderUI::BackgroundUI("Background", &scene));
	renderUIs.push_back(new SimpleRenderUI::CameraUI("Camera", &scene));
	renderUIs.push_back(new SimpleRenderUI::ObjectUI("Object", &scene));
	renderUIs.push_back(new SimpleRenderUI::ShaderUI("Shader", &scene));



	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Quit window
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);



		scene.DrawScene();

		

	

		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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

	scene.Dispose();


	std::cout << "Hello World!!" << std::endl;
	return 0; 

}





void OnWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
