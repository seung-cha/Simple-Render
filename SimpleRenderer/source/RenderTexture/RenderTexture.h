#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>
#include <string>

#include <iostream>

#include "RenderPure/Disposable.h"

namespace SimpleRender
{
	// Number of supporting textures.
	// To be expanded.
	enum TextureType
	{
		Diffuse,
		Specular
	};

	enum TextureStatus
	{
		NotReady,
		Ready
	};

	class RenderTexture : public SimpleRenderPure::Disposable
	{
	private:
		GLuint id;
		enum TextureType type;
		enum TextureStatus status = TextureStatus::NotReady;
		std::string path;

	public:
		RenderTexture(const char* path, const TextureType type);

		inline std::string* Path()
		{
			return &path;
		}
		inline enum TextureStatus Status()
		{
			return status;
		}

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
			else
				return Specular;
		}

		static inline std::string TextureTypeToString(TextureType type)
		{
			if(type == TextureType::Diffuse)
				return "Diffuse";
			else if(type == TextureType::Specular)
				return "Specular";
		}

		void Dispose() override
		{
			glDeleteTextures(1, &id);
		}


		/// <summary>
		/// Replace the current texture with the provided one.
		/// This function simply calls the function to load texture
		/// and replaces the current path to the provided one if successful.
		/// If not, nothing occurs.
		/// </summary>
		/// <param name="path"></param>
		inline void Replace(const char* path)
		{
			if(LoadTexture(path))
				this->path = path;
		}

	private:
		bool LoadTexture(const char* path);
	};

}