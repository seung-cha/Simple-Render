#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "RenderPure/Disposable.h"

#include <unordered_set>
#include <memory>		// unique ptr
#include <iostream>

namespace SimpleRenderUI
{
	class RenderUI;
}


namespace SimpleRender
{

	struct AppStatus
	{
		int Width;
		int Height;
		bool SleepMode;
		std::string Title = "Simple Render";

		inline void UpdateWindowSizeStatus(int newWidth, int newHeight)
		{
			Width = newWidth;
			Height = newHeight;
			SleepMode = Width == Height && Width == 0;

		}

		AppStatus(int width, int height)
		{
			Width = width;
			Height = height;
			SleepMode = false;
		}

		AppStatus()
		{
			Width = 1920;
			Height = 1080;
			SleepMode = false;
		}
		

	};
	

	class RenderScene;
	class SimpleRenderUI::RenderUI;

	class RenderApplication : public SimpleRenderPure::Disposable
	{
	public:
		RenderApplication();
		bool Run();


		void AddUI(SimpleRenderUI::RenderUI* widget);

		void Dispose() override;



		/// <summary>
		/// DO NOT WRITE TO THIS
		/// </summary>
		AppStatus* Status = &status;



	private:
		void UpdateWidgets();

		GLFWwindow* window = nullptr;
		RenderScene* scene = nullptr;

		// Change this to unique_ptr later
		std::unordered_set<SimpleRenderUI::RenderUI*> widgets;


		AppStatus status;
	};



}