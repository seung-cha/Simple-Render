#include "RenderObject.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderScene/RenderScene.h"


using namespace SimpleRender;
using namespace std;
using namespace Assimp;

RenderObject::RenderObject(RenderScene* scene, RenderShaderProgram* program, const string path)
{

	shaderProgram = program;
	shaderProgram->AssociatedObjects->insert(this);

	this->scene = scene;

	Position = glm::vec3(0.0f);
	Rotation = glm::vec3(0.0f);
	Scale = glm::vec3(1.0f);
	if(strcmp(path.c_str(), "") == 0)
	{
		// Load Default Mesh
		LoadDefaultMesh();
		return;
	}

	LoadMesh(path);

}

RenderObject::~RenderObject()
{

}

void RenderObject::LoadMesh(const std::string path)
{
	directory = path.substr(0, path.find_last_of('/')) + '/';
	cout << "Loading a model located in: " << endl;
	cout << path << endl << endl;

	Importer importer;

	unsigned int flags = aiProcess_Triangulate | aiProcess_GenNormals;
	const aiScene* scene = importer.ReadFile(path, flags);


	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		cerr << "Import was unsuccessful: " << endl;
		cerr << importer.GetErrorString() << endl << endl;
		LoadDefaultMesh();
		return;
	}


	InitMeshes(scene, scene->mRootNode);
}

void RenderObject::InitMeshes(const aiScene* scene, const aiNode* node)
{
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		auto indices = LoadTexturesFromMesh(scene->mMaterials[mesh->mMaterialIndex]);

		meshes.push_back(RenderMesh(scene, mesh, indices));
		
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		//Recursively add meshes for child meshes
		InitMeshes(scene, node->mChildren[i]);
	}

}

vector<unsigned int> RenderObject::LoadTexturesFromMesh(aiMaterial* material)
{
	vector<unsigned int> indices;

	vector<unsigned int> diffuseIndices = LoadTexture(material, aiTextureType_DIFFUSE);
	vector<unsigned int> specularIndices = LoadTexture(material, aiTextureType_SPECULAR);

	indices.insert(indices.end(), diffuseIndices.begin(), diffuseIndices.end());
	indices.insert(indices.end(), specularIndices.begin(), specularIndices.end());

	return indices;
}

vector<unsigned int> RenderObject::LoadTexture(aiMaterial* material, aiTextureType type)
{
	vector<unsigned int> vec;

	for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		bool exists = false;
		aiString path_;
		material->GetTexture(type, i, &path_);
		
		// Append the texture directory
		// to ignore same textures on different meshes.
		ostringstream stream;
		stream << directory << path_.C_Str();

		string path = stream.str();

		for(unsigned int i = 0; i < TextureMap.size(); i++)
		{
			if(TextureMap[i]->Equal(path.c_str()))
			{
				// Duplicate texture found.
				// Simply get the index of that texture.
				vec.push_back(i);
				exists = true;
				break;
			}
		}

		if(!exists)
		{
			enum TextureType textureType = RenderTexture::aiTextureTypeToTextureType(type);
			TextureMap.push_back(new RenderTexture(path.c_str(), textureType));
			// Get the index of the recently-pushed texture since the mesh depends on it.
			vec.push_back(TextureMap.size() - 1);
		}
	}
	return vec;

}




RenderMesh RenderObject::CreateMesh(const aiScene* scene, const aiMesh* mesh)
{

	return RenderMesh(scene, mesh, vector<unsigned int>());
}

void RenderObject::LoadDefaultMesh()
{
	cout << "Loading a default mesh" << endl << endl;

	// Get the default model
	// and set transforms specific to this model
	LoadMesh("models/default/Gibson A1.obj"); 
	Position.z = -50.0f;
	
}

void RenderObject::Draw()
{
	//Do not draw if the shader program is invalid.
	if(!shaderProgram)
		return;


	glUseProgram(shaderProgram->ID());

	// Apply transformation
	// Consider changing order of effects
	glm::mat4 transform(1.0f);
	
	transform = glm::translate(transform, Position);

	transform = glm::scale(transform, Scale);

	transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Model"), 1, GL_FALSE, &transform[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.View"), 1,
		GL_FALSE, &scene->ActiveCamera->ViewMatrix()[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Perspective"), 1,
		GL_FALSE, &scene->ActiveCamera->PerspectiveMatrix()[0][0]);



	glUseProgram(0);

	for(auto& mesh : meshes)
	{
		mesh.Draw(shaderProgram, TextureMap);
	}

}



