#pragma once

#include "RenderUI/RenderUI.h"

namespace SimpleRender
{
	class RenderObject;
}

namespace SimpleRenderUI
{
	class HierarchyUI : public RenderUI
	{
	public:
		HierarchyUI(SimpleRender::RenderApplication* const& application, const std::string& title="Scene Hierarchy");



	private:
		void DrawObjectHierarchy(SimpleRender::RenderObject* obj);


		// Inherited via RenderUI
		virtual void UpdateWidget() override;


	};
}