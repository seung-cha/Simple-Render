#pragma once

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

namespace SimpleRenderPure
{
	class ContiguousKeyInput;
	class DiscreteKeyInput;
	class MousePositionInput;

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

		

		void ProcessInput();

		/// <summary>
		/// Register an object to receive contiguous key input.
		/// </summary>
		void RegisterContiguousKeyInput(SimpleRenderPure::ContiguousKeyInput* keyInput);
		void UnregisterContiguousKeyInput(SimpleRenderPure::ContiguousKeyInput* keyInput);

		/// <summary>
		/// Register an object to receive discrete key input.
		/// </summary>
		void RegisterDiscreteKeyInput(SimpleRenderPure::DiscreteKeyInput* keyInput);
		void UnregisterDiscreteKeyInput(SimpleRenderPure::DiscreteKeyInput* keyInput);


		void RegisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput);
		void UnregisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput);


		/// <summary>
		/// DO NOT WRITE TO THIS
		/// </summary>
		AppStatus* const Status = &status;
		RenderScene*& Scene = scene;


		/// <summary>
		/// Do not use; needed to communicate in glfw callback
		/// </summary>
		std::unordered_set<SimpleRenderPure::DiscreteKeyInput*>* const DiscreteKeyInputs = &discreteKeyInputs;
		std::unordered_set<SimpleRenderPure::MousePositionInput*>* const MousePositionInputs = &mousePositionInput;


	private:
		void UpdateWidgets();

		GLFWwindow* window = nullptr;
		RenderScene* scene = nullptr;

		// Change this to unique_ptr later
		std::unordered_set<SimpleRenderUI::RenderUI*> widgets;

		std::unordered_set<SimpleRenderPure::ContiguousKeyInput*> contiguousKeyInputs;
		std::unordered_set<SimpleRenderPure::DiscreteKeyInput*> discreteKeyInputs;
		std::unordered_set<SimpleRenderPure::MousePositionInput*> mousePositionInput;


		AppStatus status;
	};



}