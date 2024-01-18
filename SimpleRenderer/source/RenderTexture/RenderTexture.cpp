#include "RenderTexture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


using namespace SimpleRender;
using namespace std;

RenderTexture::RenderTexture(const char* path, const TextureType type)
{
	// To do:
	// Gotta find a place  to put this.
	stbi_set_flip_vertically_on_load(true);


	this->path = "";
	this->type = type;
	glGenTextures(1, &id);

	if(LoadTexture(path))
		this->path = path;
}


bool RenderTexture::LoadTexture(const char* path)
{

	cout << "Generating a new texture:" << endl;
	cout << path << endl;

	int x, y, chan;
	unsigned char* img = stbi_load(path, &x, &y, &chan, 0);

	glBindTexture(GL_TEXTURE_2D, id);

	// Texture parameters. Might make this option changeable later.
	//std::cout << glGetError() << std::endl;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	if(!img)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		cerr << "Failed: could not load the image. " << path << endl << endl;
		stbi_image_free(img);
		return false;
	}



	// Defaulting to GL_RGB
	GLenum texType = GL_RGB;

	switch(chan)
	{
	case 1:
		texType = GL_RED;
		break;
	case 3:
		texType = GL_RGB;
		break;
	case 4:
		texType = GL_RGBA;
		break;
	default:
		cerr << "Warning: Texture channel is " << chan << ". " << path << endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, texType, x, y, 0, texType, GL_UNSIGNED_BYTE, img);


	cout << "Texture Generated successfully." << endl << endl;

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(img);
	status = TextureStatus::Ready;
	return true;
}

