#pragma once

#include <glad/glad.h>

#include "RenderTexture/RenderTexture.h"
#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderMesh/RenderMesh.h"

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>


namespace SimpleRender
{
	class RenderScene;

	class RenderObject
	{
	public:
		RenderObject(RenderScene* scene, RenderShaderProgram* program, const std::string path = "");
		~RenderObject();
		void Draw();


		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
		std::vector<RenderTexture*> TextureMap;

		inline std::vector<RenderTexture*> TextureMapOfType(enum TextureType type)
		{
			std::vector<RenderTexture*> tex;
			for(RenderTexture* texture : TextureMap)
			{
				if(texture->Type() == type)
					tex.push_back(texture);
			}

			return tex;
		}

		/// <summary>
		/// Replace the current shader program with the provided one.
		/// Assumes the arugment is valid.
		/// </summary>
		/// <param name="program"></param>
		inline void ReplaceShaderProgram(RenderShaderProgram* program)
		{
			if(shaderProgram)
			{
				shaderProgram->AssociatedObjects->erase(this);
			}

			shaderProgram = program;

			if(shaderProgram)
			{
				shaderProgram->AssociatedObjects->insert(this);
			}
		}

	private:
		std::vector<RenderMesh> meshes;
		RenderScene* scene;
		RenderShaderProgram* shaderProgram;
		
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