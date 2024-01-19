#include "RenderObject.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderScene/RenderScene.h"
#include "RenderCamera/RenderCamera.h"

using namespace SimpleRender;
using namespace std;
using namespace Assimp;

RenderObject::RenderObject(RenderScene* scene, RenderShaderProgram* program, int ID, const string path)
{
	this->id = ID;
	shaderProgram = program;
	shaderProgram->AssociatedObjects->insert(this);

	this->scene = scene;


	if(path == "")
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

		for(unsigned int i = 0; i < textures.size(); i++)
		{
			if(textures[i]->Equal(path))
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
			textures.push_back(new RenderTexture(textureType, path.c_str()));
			// Get the index of the recently-pushed texture since the mesh depends on it.
			vec.push_back(textures.size() - 1);
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
	
}

void RenderObject::Draw(RenderCamera* camera)
{
	//Do not draw if the shader program is invalid.
	if(!shaderProgram)
		return;


	glUseProgram(shaderProgram->ID());


	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Model"), 1, GL_FALSE, &matrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.View"), 1,
		GL_FALSE, &camera->ViewMatrix()[0][0]);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Perspective"), 1,
		GL_FALSE, &camera->PerspectiveMatrix()[0][0]);



	glUseProgram(0);

	for(auto& mesh : meshes)
	{
		mesh.Draw(shaderProgram, textures);
	}

}

void RenderObject::Draw(RenderCamera* camera, RenderShaderProgram* shaderProgram)
{
	glUseProgram(shaderProgram->ID());

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Model"), 1, GL_FALSE, &matrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.View"), 1,
		GL_FALSE, &camera->ViewMatrix()[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Perspective"), 1,
		GL_FALSE, &camera->PerspectiveMatrix()[0][0]);


	glUseProgram(0);

	for(auto& mesh : meshes)
	{
		mesh.Draw(shaderProgram, textures);
	}

}





void RenderObject::DrawID(RenderCamera* camera, RenderShaderProgram* selectionProgram)
{
	//Do not draw if the shader program is invalid.
	if(!shaderProgram)
		return;


	glUseProgram(selectionProgram->ID());


	glUniformMatrix4fv(glGetUniformLocation(selectionProgram->ID(), "transform.Model"), 1, GL_FALSE, &matrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(selectionProgram->ID(), "transform.View"), 1,
		GL_FALSE, &camera->ViewMatrix()[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(selectionProgram->ID(), "transform.Perspective"), 1,
		GL_FALSE, &camera->PerspectiveMatrix()[0][0]);

	glUniform1i(glGetUniformLocation(selectionProgram->ID(), "objectID"), id);
	glUseProgram(0);

	for(auto& mesh : meshes)
	{
		mesh.DrawID(selectionProgram);
	}
}
