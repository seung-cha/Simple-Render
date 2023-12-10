#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>


#include "RenderScene/RenderScene.h"

namespace SimpleRender
{

	class RenderApplication
	{
	public:
		RenderApplication();
		bool Run();


		template<typename T>
		void AddUI(T widget);



	private:
		GLFWwindow* window = nullptr;
		RenderScene* scene = nullptr;

		int width = 1920;
		int height = 1080;
		std::string title = "Simple Render";


	};



}