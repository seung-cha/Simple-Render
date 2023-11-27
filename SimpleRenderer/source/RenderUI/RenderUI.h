#pragma once

#include "imgui.h"
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <RenderScene/RenderScene.h>


namespace SimpleRenderUI
{
	class RenderUI
	{
	public:
		inline RenderUI(std::string title, SimpleRender::RenderScene* scene)
		{
			this->title = title;
			this->scene = scene;
		}

		/// <summary>
		/// Update the UI, receiving input but not applying them
		/// </summary>
		virtual void UpdateWidget() = 0;
		/// <summary>
		/// Update the applicationw with received inputs
		/// </summary>
		virtual inline void ReflectUpdate() = 0;

	protected:
		std::string title;
		SimpleRender::RenderScene* scene;
		
	};

}