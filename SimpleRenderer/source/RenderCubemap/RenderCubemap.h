#pragma once

#include <glad/glad.h>

#include <vector>
#include <string>

#include "RenderShaderProgram/RenderShaderProgram.h"

namespace SimpleRender
{
	enum CubemapSide
	{
		/// <summary>
		/// GL_TEXTURE_CUBE_MAP_POSITIVE_X
		/// </summary>
		Right,

		/// <summary>
		/// GL_TEXTURE_CUBE_MAP_NEGATIVE_X
		/// </summary>
		Left,

		/// <summary>
		/// GL_TEXTURE_CUBE_MAP_POSITIVE_Y
		/// </summary>
		Top,

		/// <summary>
		/// GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
		/// </summary>
		Bottom,

		/// <summary>
		/// GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		/// </summary>
		Front,

		/// <summary>
		/// GL_TEXTURE_CUBE_MAP_POSITIVE_Z
		/// </summary>
		Back

	};



	class RenderCubemap
	{
	public:
		RenderCubemap();

		/// <summary>
		/// Set given side with the provided image
		/// </summary>
		/// <param name=""></param>
		/// <param name="path"></param>
		void SetSide(enum CubemapSide side, std::string path);

		//
		void Draw(class RenderCamera* camera);


	private:
		unsigned char* imgData[6] = {0};
		GLuint id;
		RenderShaderProgram* shaderProgram;
		GLuint VAO, VBO;

	};




}