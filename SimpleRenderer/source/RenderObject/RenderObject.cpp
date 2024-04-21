#include "RenderObject.h"

#include <iostream>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <memory>

#include "RenderScene/RenderScene.h"
#include "RenderCamera/RenderCamera.h"

using namespace SimpleRender;
using namespace std;
using namespace Assimp;

RenderObject::RenderObject(RenderScene* scene, RenderShaderProgram* program, int ID, const aiScene* aiScene, const aiNode* node, RenderObject* parent)
{
	this->id = ID;
	this->scene = scene;
	this->parent = parent;

	this->absoluteParent = parent->absoluteParent ? parent->absoluteParent : parent;

	this->shaderProgram = program;
	shaderProgram->AssociatedObjects->insert(this);


	InitMeshes(aiScene, node);

}

RenderObject::RenderObject(RenderScene* scene, RenderShaderProgram* program, int ID, const string path)
{
	this->id = ID;
	shaderProgram = program;
	shaderProgram->AssociatedObjects->insert(this);

	this->scene = scene;

	this->absoluteParent = this;


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
	// Unlink the parent

	for(auto& obj : children)
	{
		ReplaceShaderProgram(nullptr);
	}


	ReplaceShaderProgram(nullptr);
}

void RenderObject::LoadDefaultMesh()
{
	cout << "Loading a default mesh" << endl << endl;

	// Get the default model
	// and set transforms specific to this model
	LoadMesh("models/default/Gibson A1.obj");
	Transform->Position.z = -50.0f;

}



void RenderObject::LoadMesh(const std::string path)
{
	directory = path.substr(0, path.find_last_of('/')) + '/';
	cout << "Loading a model located in: " << endl;
	cout << path << endl << endl;

	Importer importer;

	unsigned int flags = aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace;
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
		meshes.push_back(std::make_unique<SimpleRender::RenderMesh>(scene, mesh, indices));
	}
	
	
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		//Recursively create children
		if(i > 0)
		{
			RenderObject* obj = new RenderObject(this->scene, this->shaderProgram,
				this->scene->SceneObjects->size() + 1, scene, node->mChildren[i], this);

			aiVector3D scale, translate;
			aiQuaternion rotation;
			
			obj->name = node->mChildren[i]->mName.C_Str();
			node->mChildren[i]->mTransformation.Decompose(scale, rotation, translate);
			
			
			// Convert quaternion to Euler
			glm::quat q(rotation.w, rotation.x, rotation.y, rotation.z);
			glm::vec3 eulerRot = glm::eulerAngles(q);

			printf("%f, %f, %f\n", eulerRot.x, eulerRot.y, eulerRot.z);

			printf(node->mChildren[i]->mParent == nullptr ? "No parent\n" : "Parent\n");


			obj->Transform->Position = glm::vec3(translate.x, translate.y, translate.z);
			obj->Transform->Scale = glm::vec3(scale.x, scale.y, scale.z);
			obj->Transform->Rotation = eulerRot * (180.0f / 3.141592f);


			this->scene->SceneObjects->push_back(std::unique_ptr<SimpleRender::RenderObject>(obj));
			children.insert(obj);
		}
		else
		{

			aiVector3D scale, translate;
			aiQuaternion rotation;

			name = node->mChildren[i]->mName.C_Str();
			node->mChildren[i]->mTransformation.Decompose(scale, rotation, translate);


			// Convert quaternion to Euler
			glm::quat q(rotation.w, rotation.x, rotation.y, rotation.z);
			glm::vec3 eulerRot = glm::eulerAngles(q);


			transform.Position = glm::vec3(translate.x, translate.y, translate.z);
			transform.Scale = glm::vec3(scale.x, scale.y, scale.z);
			transform.Rotation = eulerRot * (180.0f / 3.141592f);


			InitMeshes(scene, node->mChildren[i]);
		}
	}

}

vector<unsigned int> RenderObject::LoadTexturesFromMesh(aiMaterial* material)
{
	vector<unsigned int> indices;

	vector<unsigned int> diffuseIndices = LoadTexture(material, aiTextureType_DIFFUSE);
	vector<unsigned int> specularIndices = LoadTexture(material, aiTextureType_SPECULAR);
	vector<unsigned int> normalIndices = LoadTexture(material, aiTextureType_HEIGHT);

	//std::cout << "Normal map size: " << normalIndices.size() << std::endl << std::endl;

	indices.insert(indices.end(), diffuseIndices.begin(), diffuseIndices.end());
	indices.insert(indices.end(), specularIndices.begin(), specularIndices.end());
	indices.insert(indices.end(), normalIndices.begin(), normalIndices.end());


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


void RenderObject::Draw(RenderCamera* camera)
{
	//Do not draw if the shader program is invalid.
	if(!shaderProgram)
		return;


	glm::mat4 matrix(1.0f);

	if(parent)
	{
		matrix = parent->Transform->LocalMatrix() * Transform->LocalMatrix();
	}
	else
		matrix = Transform->LocalMatrix();



	/*for(auto& i : children)
	{
		i->Draw(camera);
	}*/



	glUseProgram(shaderProgram->ID());


	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Model"), 1, GL_FALSE, &matrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.View"), 1,
		GL_FALSE, &camera->ViewMatrix()[0][0]);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Perspective"), 1,
		GL_FALSE, &camera->PerspectiveMatrix()[0][0]);



	glUseProgram(0);

	for(auto& mesh : meshes)
	{
		mesh->Draw(shaderProgram, textures);
	}

}

void RenderObject::Draw(RenderCamera* camera, RenderShaderProgram* shaderProgram)
{
	glm::mat4 matrix(1.0f);

	if(parent)
	{
		matrix = parent->Transform->LocalMatrix() * Transform->LocalMatrix();
	}
	else
		matrix = Transform->LocalMatrix();



	glUseProgram(shaderProgram->ID());

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Model"), 1, GL_FALSE, &matrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.View"), 1,
		GL_FALSE, &camera->ViewMatrix()[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Perspective"), 1,
		GL_FALSE, &camera->PerspectiveMatrix()[0][0]);


	glUseProgram(0);

	for(auto& mesh : meshes)
	{
		mesh->Draw(shaderProgram, textures);
	}

}





void RenderObject::DrawID(RenderCamera* camera, RenderShaderProgram* selectionProgram)
{
	//Do not draw if the shader program is invalid.
	if(!shaderProgram)
		return;

	if(parent)
	{
		matrix = parent->Transform->LocalMatrix() * Transform->LocalMatrix();
	}
	else
		matrix = Transform->LocalMatrix();


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
		mesh->DrawID(selectionProgram);
	}
}
