#pragma once

#include "imgui.h"
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>


namespace SimpleRender
{
	class RenderApplication;
}

namespace SimpleRenderUI
{
	class RenderUI
	{
	public:
		RenderUI(const std::string& title, SimpleRender::RenderApplication* const& application) : title{ title }, application{ application }
		{
		}

		virtual ~RenderUI() {};

		/// <summary>
		/// Update the UI, receiving input but not applying them
		/// </summary>
		virtual void UpdateWidget() = 0;

	protected:
		std::string title;
		SimpleRender::RenderApplication* application;
		
	};

}