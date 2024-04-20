#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>

#include <iostream>
#include <string>


namespace SimpleRender
{
	// Number of supporting textures.
	// To be expanded.
	enum TextureType
	{
		Diffuse,
		Specular,
		Normal,
	};

	enum TextureStatus
	{
		NotReady,
		Ready
	};

	class RenderTexture
	{
	private:
		GLuint id;
		enum TextureType type;
		enum TextureStatus status = TextureStatus::NotReady;
		std::string path;

	public:
		RenderTexture(const TextureType type, std::string path = "");
		~RenderTexture();

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

		/// <summary>
		/// True if the provided path is the same as this texture source
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		inline bool Equal(const std::string& path)
		{
			return this->path == path;
		}


		static inline enum TextureType aiTextureTypeToTextureType(aiTextureType type)
		{
			if(type == aiTextureType_DIFFUSE)
				return Diffuse;
			else if(type == aiTextureType_SPECULAR)
				return Specular;
			else if(type == aiTextureType_HEIGHT)
				return Normal;
			else
				return Normal;
		}

		static inline std::string TextureTypeToString(TextureType type)
		{
			if(type == TextureType::Diffuse)
				return "Diffuse";
			else if(type == TextureType::Specular)
				return "Specular";
			else if(type == TextureType::Normal)
				return "Normal";
		}


		/// <summary>
		/// Send this texture to GLSL program at given location.
		/// Assumes the program is bound.
		/// </summary>
		inline void Apply(const GLuint& program, const int index = 0)
		{
			const std::string s = "material." + TextureTypeToString(type) + std::to_string(index);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, id);

			glUniform1i(glGetUniformLocation(program, s.c_str()), index);
		}


		/// <summary>
		/// Replace the current texture with the provided one.
		/// This function simply calls the function to load texture
		/// and replaces the current path to the provided one if successful.
		/// If not, nothing occurs.
		/// </summary>
		/// <param name="path"></param>
		inline void Replace(std::string path)
		{
			if(LoadTexture(path))
				this->path = path;
		}

	private:
		bool LoadTexture(std::string path);
	};

}