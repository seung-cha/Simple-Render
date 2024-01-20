#include "RenderMaterial/RenderMaterial.h"



void SimpleRender::RenderMaterial::AddTexture(const enum SimpleRender::TextureType type, std::string string)
{
	textureList.push_back(std::make_unique<SimpleRender::RenderTexture>(type, string));
}

void SimpleRender::RenderMaterial::Apply(const GLuint& program)
{

	for(int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->Apply(program, i);
	}


}