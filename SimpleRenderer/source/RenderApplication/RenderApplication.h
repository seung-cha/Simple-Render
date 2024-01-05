#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "RenderPure/Disposable.h"
#include <unordered_set>
#include <memory>		// unique ptr
#include <iostream>

#include <glm/glm.hpp>

namespace SimpleRenderUI
{
	class RenderUI;
}

namespace SimpleRenderPure
{
	class ContiguousKeyInput;
	class DiscreteKeyInput;
	class MousePositionInput;
	class DiscreteMouseInput;

}


namespace SimpleRender
{
	struct MouseStatus
	{
		MouseStatus()
		{
			xPos = yPos = lastX = lastY = 0;
			LeftClick = RightClick = false;
		}
		int xPos;
		int yPos;

		int deltaXPos;
		int deltaYPos;

		/// <summary>
		/// True for as long as LMB is held
		/// </summary>
		int LeftClick;
		/// <summary>
		/// True for as long as RMB is held
		/// </summary>
		int RightClick;

		/// <summary>
		/// The last X coordinate of the mouse
		/// </summary>
		int lastX;

		/// <summary>
		/// The last Y coordinate of the mouse
		/// </summary>
		int lastY;

		/// <summary>
		/// Equivalent to <xPos, yPos>
		/// </summary>
		glm::vec2 MouseCoordinates;

		/// <summary>
		/// Equivalent to <deltaXPos, deltaYPos>
		/// </summary>
		glm::vec2 MouseDelta;

		/// <summary>
		/// Equivalent to <lastX, lastY>
		/// </summary>
		glm::vec2 MouseLastCoordinates;

	};

	struct AppStatus
	{
		int Width;
		int Height;

		glm::vec2 Resolution;


		int FixedWidth = 1920;
		int FixedHeight = 1080;

		glm::vec2 FixedResolution = glm::vec2(FixedWidth, FixedHeight);

		bool SleepMode;
		std::string Title = "Simple Render";


		/// <summary>
		/// Time in double; default type
		/// </summary>
		double Time = 0.0;

		/// <summary>
		/// Time in float
		/// </summary>
		float Timef = 0.0f;

		/// <summary>
		/// Time in int
		/// </summary>
		int Timei = 0;


		MouseStatus* Mouse = &mouse;


		inline void UpdateWindowSizeStatus(int newWidth, int newHeight)
		{
			Width = newWidth;
			Height = newHeight;
			Resolution.x = Width;
			Resolution.y = Height;
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
			Resolution = glm::vec2(Width, Height);
			SleepMode = false;
		}


	private:
		MouseStatus mouse;
	};

	

	class RenderScene;
	class RenderDeferredRender;

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

		/// <summary>
		/// Register an object to receive mouse position input.
		/// </summary>
		void RegisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput);
		void UnregisterMousePositionInput(SimpleRenderPure::MousePositionInput* mouseInput);

		/// <summary>
		/// Register an object to receive discrete mouse button input
		/// </summary>
		void RegisterDiscreteMouseInput(SimpleRenderPure::DiscreteMouseInput* mouseInput);
		void UnregisterDiscreteMouseInput(SimpleRenderPure::DiscreteMouseInput* mouseInput);


		/// <summary>
		/// DO NOT WRITE TO THIS
		/// </summary>
		AppStatus* const Status = &status;
		
		/// <summary>
		/// DO NOT WRITE TO THIS
		/// </summary>

		RenderScene*& Scene = scene;
		

	

		/// <summary>
		/// Do not use; needed to communicate in glfw callback
		/// </summary>
		std::unordered_set<SimpleRenderPure::DiscreteKeyInput*>* const DiscreteKeyInputs = &discreteKeyInputs;
		/// <summary>
		/// Do not use; needed to communicate in glfw callback
		/// </summary>
		std::unordered_set<SimpleRenderPure::MousePositionInput*>* const MousePositionInputs = &mousePositionInputs;
		/// <summary>
		/// Do not use; needed to communicate in glfw callback
		/// </summary>
		std::unordered_set<SimpleRenderPure::DiscreteMouseInput*>* const MouseButtonInputs = &mouseButtonInputs;

	private:
		void UpdateWidgets();

		GLFWwindow* window = nullptr;
		RenderScene* scene = nullptr;

		// Change this to unique_ptr later
		std::unordered_set<SimpleRenderUI::RenderUI*> widgets;

		std::unordered_set<SimpleRenderPure::ContiguousKeyInput*> contiguousKeyInputs;
		std::unordered_set<SimpleRenderPure::DiscreteKeyInput*> discreteKeyInputs;
		std::unordered_set<SimpleRenderPure::MousePositionInput*> mousePositionInputs;
		std::unordered_set<SimpleRenderPure::DiscreteMouseInput*> mouseButtonInputs;

		AppStatus status;
	};



}