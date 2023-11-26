#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>
#include <string>

#include <iostream>

namespace SimpleRender
{
	// Number of supporting textures.
	// To be expanded.
	enum TextureType
	{
		Diffuse,
		Specular
	};

	class RenderTexture
	{
	private:
		GLuint id;
		enum TextureType type;
		std::string path;

	public:
		RenderTexture(const char* path, const TextureType type);
		~RenderTexture();
		inline GLuint ID()
		{
			return id;
		}

		inline enum TextureType Type()
		{
			return type;
		}

		inline bool Equal(const char* path)
		{
			return std::strcmp(this->path.c_str(), path) == 0;
		}

		static inline enum TextureType aiTextureTypeToTextureType(aiTextureType type)
		{
			if(type == aiTextureType_DIFFUSE)
				return Diffuse;
			else if(type == aiTextureType_SPECULAR)
				return Specular;
		}

		static inline std::string TextureTypeToString(TextureType type)
		{
			if(type == TextureType::Diffuse)
				return "Diffuse";
			else if(type == TextureType::Specular)
				return "Specular";
		}

	};

}