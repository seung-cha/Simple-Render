#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

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
		MouseStatus() {}

		int xPos = 0;
		int yPos = 0;

		int deltaXPos = 0;
		int deltaYPos = 0;

		/// <summary>
		/// True for as long as LMB is held
		/// </summary>
		int LeftClick = 0;
		/// <summary>
		/// True for as long as RMB is held
		/// </summary>
		int RightClick = 0;

		/// <summary>
		/// The last X coordinate of the mouse
		/// </summary>
		int lastX = 0;

		/// <summary>
		/// The last Y coordinate of the mouse
		/// </summary>
		int lastY = 0;

		/// <summary>
		/// Equivalent to <xPos, yPos>
		/// </summary>
		glm::vec2 MouseCoordinates = {0, 0};

		/// <summary>
		/// Equivalent to <deltaXPos, deltaYPos>
		/// </summary>
		glm::vec2 MouseDelta = {0, 0};

		/// <summary>
		/// Equivalent to <lastX, lastY>
		/// </summary>
		glm::vec2 MouseLastCoordinates = {0, 0};

	};

	struct AppStatus
	{
		AppStatus(int width, int height)
		{
			Width = width;
			Height = height;
			Resolution = glm::vec2(Width, Height);

			AspectRatio = Width / static_cast<float>(Height);

			SleepMode = false;
		}

		AppStatus()
		{
			Width = 1920;
			Height = 1080;
			Resolution.x = Width;
			Resolution.y = Height;

			AspectRatio = Width / static_cast<float>(Height);

			Resolution = glm::vec2(Width, Height);
			SleepMode = false;
		}

		inline void UpdateWindowSizeStatus(int newWidth, int newHeight)
		{
			Width = newWidth;
			Height = newHeight;
			Resolution = glm::vec2(Width, Height);


			SleepMode = Width == Height && Width == 0;

			AspectRatio = newHeight == 0 ? 0.0f : newWidth / static_cast<float>(newHeight);

		}

		int Width = 0;
		int Height = 0;

		glm::vec2 Resolution = {0, 0};

		float AspectRatio = 0.0f;

		const int FixedWidth = 1920;
		const int FixedHeight = 1080;

		float FixedAspectRatio = FixedWidth / static_cast<float>(FixedHeight);

		glm::vec2 FixedResolution = glm::vec2(FixedWidth, FixedHeight);

		bool SleepMode;
		std::string Title = "Simple Render";
		std::string SaveFile = "";

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

		MouseStatus* const Mouse = &mouse;


	private:
		MouseStatus mouse;
	};

	

	class RenderScene;
	class RenderDeferredRender;

	class RenderApplication
	{
	public:
		RenderApplication();
		~RenderApplication();
		bool Run();



		/// <summary>
		/// Create and display a UI widget.
		/// Pointer is managed internally.
		/// </summary>
		void AddUI(SimpleRenderUI::RenderUI* const& widget);

		void SaveScene();
		void SaveSceneAs();
		void LoadScene();
		

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
		AppStatus* const& Status = &status;

		/// <summary>
		/// DO NOT WRITE TO THIS
		/// </summary>
		RenderScene* const& Scene = scene;
		

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

		
		// can't turn these two into unique_ptr.
		// GLFWwindow does not define a destructor
		// RenderScene needs a const ref to itself.
		GLFWwindow* window = nullptr;
		RenderScene* scene = nullptr;

		std::unordered_set<std::unique_ptr<SimpleRenderUI::RenderUI>> widgets;

		// Map of different key input objects.
		// The owner of this must free them.
		std::unordered_set<SimpleRenderPure::ContiguousKeyInput*> contiguousKeyInputs;
		std::unordered_set<SimpleRenderPure::DiscreteKeyInput*> discreteKeyInputs;
		std::unordered_set<SimpleRenderPure::MousePositionInput*> mousePositionInputs;
		std::unordered_set<SimpleRenderPure::DiscreteMouseInput*> mouseButtonInputs;

		AppStatus status;
	};



}