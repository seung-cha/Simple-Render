#include "RenderUI/RenderUI.h"
#include "RenderObject/RenderObject.h"
#include "RenderTexture/RenderTexture.h"

namespace SimpleRenderUI
{
	class ObjectUI : public RenderUI
	{
	public:
		ObjectUI(std::string title, SimpleRender::RenderScene* scene) : RenderUI(title, scene)
		{
			this->object = scene->ActiveObject;
		}

		virtual inline void UpdateWidget()
		{
			ImGui::Begin(title.c_str());

			ImGui::DragFloat3("Position", &object->Position[0], 0.5f);
			ImGui::DragFloat3("Rotation", &object->Rotation[0], 0.5f);
			ImGui::DragFloat3("Scale", &object->Scale[0], 0.01f);

			ImGui::BeginChild("Textures");


			// Create buttons for texture replacement
			for(unsigned int i = 0; i < object->TextureMap.size(); i++)
			{
				if(object->TextureMap[i].Type() == SimpleRender::TextureType::Diffuse)
				{
					if(ImGui::Button("Diffuse"))
					{
						// Open up a file selecter and replace the texture with the selected one.
						//object->TextureMap[i].Replace("models/default/Spec1.jpg");
						
					}
				}
				else if(object->TextureMap[i].Type() == SimpleRender::TextureType::Specular)
				{
					if(ImGui::Button("Specular"))
					{

					}
				}
			}

			ImGui::EndChild();




			ImGui::End();
		}

		virtual inline void ReflectUpdate()
		{

		}

	private:
		SimpleRender::RenderObject* object;

	};

}