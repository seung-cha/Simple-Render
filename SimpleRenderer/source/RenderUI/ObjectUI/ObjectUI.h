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
			selectedTexture = nullptr; 
		}

		virtual void UpdateWidget() override;

		virtual inline void ReflectUpdate() override
		{
		}

	private:
		void TransformWidget();
		void TextureWidget();
		void FocusedTextureDetails();
		void TextureTable(enum SimpleRender::TextureType type);

		SimpleRender::RenderTexture* selectedTexture;

		ImVec2 textureButtonSize = ImVec2(64, 64);

	};

}