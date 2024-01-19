#pragma once

#include <RenderTexture/RenderTexture.h>
#include <vector>
#include <memory>
#include <glad/glad.h>

namespace SimpleRender
{
	class RenderMaterial
	{
	public:

		/// <summary>
		/// Create and append a unique ptr of RenderTexture with the provided arguments.
		/// </summary>
		/// <param name=""></param>
		/// <param name="string"></param>
		void AddTexture(const enum TextureType type, std::string string = "");

		/// <summary>
		/// Send textures to shader program. Assumes the program is bound.
		/// </summary>
		void Apply(const GLuint& program);


		const std::vector<std::unique_ptr<RenderTexture>>& TextureList = textureList;
	private:
		std::vector<std::unique_ptr<RenderTexture>> textureList;

	};



}