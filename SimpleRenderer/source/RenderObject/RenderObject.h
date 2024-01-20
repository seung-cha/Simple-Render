#pragma once

#include <glad/glad.h>

#include "RenderTexture/RenderTexture.h"
#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderMesh/RenderMesh.h"
#include "RenderPure/Disposable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <RenderMaterial/RenderMaterial.h>

namespace SimpleRender
{
	class RenderScene;
	class RenderCamera;

	struct Transform
	{
	public:
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		/// <summary>
		/// Code copied from LearnOpenGL, Scene-Graph tutorial.
		/// Return local TRS (translate * rotation * scale) matrix.
		/// Multiply this with the parent's to obtain local matrix.
		/// </summary>
		/// <returns></returns>
		glm::mat4 LocalMatrix()
		{
			
			const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0));
			const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0));
			const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0));

			const glm::mat4 rotationMatrix = transformY * transformX * transformZ;

			return glm::translate(glm::mat4(1.0f), Position) * rotationMatrix * glm::scale(glm::mat4(1.0f), Scale);
		}
	};


	class RenderObject : SimpleRenderPure::Disposable
	{
	public:
		/// <summary>
		/// Use this constructor to create a new object as a child.
		/// Calls InitMeshes() internally.
		/// </summary>
		/// <param name="scene"></param>
		/// <param name="mesh"></param>
		/// <param name="parent"></param>
		RenderObject(RenderScene* scene, RenderShaderProgram* program, int ID, const aiScene* aiScene, const aiNode* node, RenderObject* parent = nullptr);
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



		std::vector<RenderTexture*>* TextureMap = &textures;
		
		Transform* Transform = &transform;
		glm::mat4& Matrix = matrix;
		std::string& Name = name;
		RenderObject*& Parent = parent;
		std::vector<RenderObject*>* Children = &children;

		const int& ID = id;


		inline void SetID(int newID)
		{
			id = newID;
		}

	private:
		RenderScene* scene;

		int id;
		std::string name;
		SimpleRender::Transform transform;
		glm::mat4 matrix = glm::mat4(1.0f);



		std::vector<RenderMesh> meshes;			// To delete
		std::vector<RenderTexture*> textures;	// To delete



		RenderObject* parent = nullptr;
		std::vector<RenderObject*> children;
		RenderMaterial* material;

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