#pragma once

#include <glad/glad.h>

#include "RenderTexture/RenderTexture.h"
#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderMesh/RenderMesh.h"
#include "RenderPure/Disposable.h"

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>


namespace SimpleRender
{
	class RenderScene;
	class RenderCamera;

	class RenderObject : SimpleRenderPure::Disposable
	{
	public:
		RenderObject(RenderScene* scene, RenderShaderProgram* program, int ID, const std::string path = "");
		~RenderObject();
		void Draw(RenderCamera* camera);

		/// <summary>
		/// Draw the object with given shader program instead. Assumes the program is valid.
		/// </summary>
		/// <param name="camera"></param>
		/// <param name="shaderProgram"></param>
		void Draw(RenderCamera* camera, RenderShaderProgram* shaderProgram);


		/// <summary>
		/// Draw call for object selection
		/// </summary>
		/// <param name="camera"></param>
		void DrawID(RenderCamera* camera, RenderShaderProgram* selectionProgram);


		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
		std::vector<RenderTexture*>* TextureMap = &textures;

		inline std::vector<RenderTexture*> TextureMapOfType(enum TextureType type)
		{
			std::vector<RenderTexture*> tex;
			for(RenderTexture* texture : textures)
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


		inline void Dispose() override
		{
			for(auto& texture : textures)
			{
				texture->Dispose();
			}

			for(auto& mesh : meshes)
			{
				mesh.Dispose();
			}
		}

		
		glm::mat4& Matrix = matrix;
		std::string& Name = name;

		const int& ID = id;


		inline void SetID(int newID)
		{
			id = newID;
		}

	private:

		int id;
		std::string name;
		glm::mat4 matrix = glm::mat4(1.0f);

		std::vector<RenderMesh> meshes;
		std::vector<RenderTexture*> textures;
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