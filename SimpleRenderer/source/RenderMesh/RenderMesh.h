#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>
#include <vector>

#include "RenderVertex/RenderVertex.h"
#include "RenderTexture/RenderTexture.h"



namespace SimpleRender
{
	class RenderShaderProgram;

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
		RenderMesh() {};
		/// <summary>
		/// Initialise Mesh
		/// </summary>
		/// <param name="scene">aiScene obtained from Assimp Importer</param>
		/// <param name="mesh">aiMesh instance obtained from mRootNode</param>
		/// <param name="textureIndices">texture slots to use, mapped onto the texture vector in the object class</param>
		RenderMesh(const aiScene* const& scene, const aiMesh* const& mesh, const std::vector<unsigned int> & textureIndices);
		~RenderMesh();
		void Draw(RenderShaderProgram* const& program, const std::vector<RenderTexture*>& textureMap);

		/// <summary>
		/// Draw call for object selection. This is really just glDrawElements.
		/// </summary>
		/// <param name="program"></param>
		void DrawID(RenderShaderProgram* const& program);


	private:
		/// <summary>
		/// Populate vertices
		/// </summary>
		void InitVertices(const aiMesh* const& mesh);
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