#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>
#include <vector>

#include "RenderVertex/RenderVertex.h"
#include "RenderTexture/RenderTexture.h"


namespace SimpleRender
{
	enum BufferType
	{
		VBO,
		EBO,
		// Number of buffers
		LEN = 2
	};


	class RenderMesh
	{
	public:
		/// <summary>
		/// Initialise Mesh
		/// </summary>
		/// <param name="scene">aiScene obtained from Assimp Importer</param>
		/// <param name="mesh">aiMesh instance obtained from mRootNode</param>
		/// <param name="textureIndices">texture slots to use, mapped onto the texture vector in the object class</param>
		RenderMesh(const aiScene* scene, const aiMesh* mesh, const std::vector<unsigned int> textureIndices);
		~RenderMesh();
		void Draw(GLuint program, std::vector<RenderTexture>& textureMap);

	private:
		/// <summary>
		/// Populate vertices
		/// </summary>
		void InitVertices(const aiMesh* mesh);
		/// <summary>
		/// Initialise buffers
		/// </summary>
		void InitBuffers();


		std::vector<RenderVertex> vertices;
		std::vector<unsigned int> textureIndices;

		// indices for element buffer
		std::vector<unsigned int> elementIndices;
		GLuint vertexArray;
		GLuint buffers[BufferType::LEN];

	};

}