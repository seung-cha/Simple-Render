#pragma once

#include <glad/glad.h>
#include "RenderMesh/RenderMesh.h"
#include "RenderTexture/RenderTexture.h"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>


namespace SimpleRender
{
	
	class RenderObject
	{
	public:
		RenderObject(const std::string path = "");
		~RenderObject();
		void Draw(GLuint program);


		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
		std::vector<RenderTexture> TextureMap;


	private:
		std::vector<RenderMesh> meshes;
		
		void LoadMesh(const std::string path);

		/// <summary>
		/// Populate this instance with data from Assimp.
		/// aiScene contains data such as meshes and textures
		///	Each aiNode in the scene holds references to those
		/// 
		/// The entry point is mRootNode.
		/// </summary>
		/// <param name="node">Initially the root node, scene->mRootNode</param>
		/// <param name="scene">aiScene gathered from Importer.ReadFile</param>
		void InitMeshes(const aiScene* scene, const aiNode* node);
		/// <summary>
		/// Given an aiMesh, convert it into a useful RenderMesh.
		/// </summary>
		/// <param name="scene">aiScene from an instance of Importer</param>
		/// <param name="node">aiMesh obtained from an instance of aiScene</param>
		/// <returns></returns>
		RenderMesh CreateMesh(const aiScene* scene, const aiMesh* mesh);

		std::vector<unsigned int> LoadTexturesFromMesh(aiMaterial* material);
		std::vector<unsigned int> LoadTexture(aiMaterial* material, aiTextureType type);
		std::string directory;
		void LoadDefaultMesh();


	};



}