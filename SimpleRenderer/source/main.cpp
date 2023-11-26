#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "FileReader/FileReader.h"
#include "RenderObject/RenderObject.h"
#include "RenderCamera/RenderCamera.h"

#include "RenderTexture/RenderTexture.h"


#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "RenderUI/RenderUI.h"
#include "RenderUI/BackgroundUI/BackgroundUI.h"
#include "RenderUI/CameraUI/CameraUI.h"
#include "RenderUI/ObjectUI/ObjectUI.h"





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
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);



	SimpleRender::RenderObject obj("");
	
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


	//Debugging stuff
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	float cube[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint VAO, VBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);

	SimpleRender::RenderCamera cam;


	glm::mat4 model = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");


	// UI widgets
	std::vector<SimpleRenderUI::RenderUI*> renderUIs;
	renderUIs.push_back(new SimpleRenderUI::BackgroundUI("Background"));
	renderUIs.push_back(new SimpleRenderUI::CameraUI("Camera", &cam));
	renderUIs.push_back(new SimpleRenderUI::ObjectUI("Object", &obj));



	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		cam.Update();
		// Quit window
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);





		glUseProgram(program);

		glUniformMatrix4fv(glGetUniformLocation(program, "transform.Projection"), 1, GL_FALSE, &cam.Perspective()[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "transform.View"), 1, GL_FALSE, &cam.ViewMatrix()[0][0]);

		glUseProgram(0);


		obj.Draw(program);

	

		/*std::cout << glGetError() << std::endl;
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glUseProgram(0);*/

		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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
		free(ui);
	}


	std::cout << "Hello World!!" << std::endl;
	return 0; 

}