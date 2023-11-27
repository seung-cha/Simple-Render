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
			selectedTexture = nullptr; 
		}

		virtual void UpdateWidget();

		virtual inline void ReflectUpdate()
		{

		}

	private:
		void TransformWidget();
		void TextureWidget();
		void FocusedTextureDetails();
		void TextureTable(enum SimpleRender::TextureType type);

		SimpleRender::RenderObject* object;
		SimpleRender::RenderTexture* selectedTexture;

		ImVec2 textureButtonSize = ImVec2(64, 64);

	};

}