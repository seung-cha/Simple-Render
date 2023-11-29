#pragma once

#include "RenderUI/RenderUI.h"


namespace SimpleRenderUI
{
	class HierarchyUI : public RenderUI
	{
	public:
		HierarchyUI(std::string title, SimpleRender::RenderScene* scene);



		// Inherited via RenderUI
		virtual void UpdateWidget() override;

		virtual inline void ReflectUpdate() override
		{

		}

	};
}