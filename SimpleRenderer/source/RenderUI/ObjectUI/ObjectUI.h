#include "RenderUI/RenderUI.h"
#include "RenderObject/RenderObject.h"
#include "RenderTexture/RenderTexture.h"

namespace SimpleRenderUI
{
	class ObjectUI : public RenderUI
	{
	public:
		ObjectUI(SimpleRender::RenderApplication* const& application, const std::string& title = "Objects");


		virtual void UpdateWidget() override;


	private:
		void TransformWidget();
		void TextureWidget();
		void FocusedTextureDetails();
		void TextureTable(enum SimpleRender::TextureType type);

		SimpleRender::RenderTexture* selectedTexture;

		ImVec2 textureButtonSize = ImVec2(64, 64);

	};

}