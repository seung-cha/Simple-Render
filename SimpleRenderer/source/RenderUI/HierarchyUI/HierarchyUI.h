#pragma once

#include "RenderUI/RenderUI.h"


namespace SimpleRenderUI
{
	class HierarchyUI : public RenderUI
	{
	public:
		HierarchyUI(SimpleRender::RenderApplication* application, std::string title="Scene Hierarchy");



		// Inherited via RenderUI
		virtual void UpdateWidget() override;

		virtual inline void ReflectUpdate() override
		{

		}

	};
}