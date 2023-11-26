#include "RenderUI/RenderUI.h"
#include "RenderObject/RenderObject.h"

namespace SimpleRenderUI
{
	class ObjectUI : public RenderUI
	{
	public:
		ObjectUI(std::string title, SimpleRender::RenderObject* object) : RenderUI(title)
		{
			this->object = object;
		}

		virtual inline void UpdateWidget()
		{
			ImGui::Begin(title.c_str());

			ImGui::DragFloat3("Position", &object->Position[0], 0.5f);
			ImGui::DragFloat3("Rotation", &object->Rotation[0], 0.5f);
			ImGui::DragFloat3("Scale", &object->Scale[0], 0.01f);




			ImGui::End();
		}

		virtual inline void ReflectUpdate()
		{

		}

	private:
		SimpleRender::RenderObject* object;

	};

}