#include "RenderJson.h"

#include "RenderObject/RenderObject.h"
#include "RenderScene/RenderScene.h"

#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderShader/RenderShader.h"

#include <string>


void SimpleRender::to_json(json& j, const RenderObject* const& obj)
{

	j["id"] = obj->ID;
	j["name"] = obj->Name;
	j["path"] = obj->Path;
	j["transform"]["position"] = obj->Transform->Position;
	j["transform"]["rotation"] = obj->Transform->Rotation;
	j["transform"]["scale"] = obj->Transform->Scale;
}

SimpleRender::RenderObject* SimpleRender::InstantiateRenderObjectFromJson(const json& j)
{
	std::string str = j["path"].get<std::string>();
	std::cout << "Str: " << str << std::endl;
	return nullptr;
}



void SimpleRender::to_json(json& j, const RenderScene* const& scene)
{
	for(auto& obj : *scene->SceneObjects)
	{
		// Only add objects that have path
		// Since some objects are instantiated as child
		if(obj->Path.size() > 0)
		{
			j["object"] += obj.get();
		}
	}

}

bool SimpleRender::LoadSceneFromJson(const json& j, RenderScene* const& scene)
{
	scene->SceneVertexShaders->push_back(std::make_unique<RenderShader>(ShaderType::Vertex, "shaders/debug/debug.vert"));
	scene->SceneFragmentShaders->push_back(std::make_unique<RenderShader>(ShaderType::Fragment, "shaders/debug/debug.frag"));

	scene->SceneShaderPrograms->push_back(std::make_unique<RenderShaderProgram>());

	RenderShaderProgram* prog = (*scene->SceneShaderPrograms)[0].get();

	prog->AttachShader((*scene->SceneVertexShaders)[0].get());
	prog->AttachShader((*scene->SceneFragmentShaders)[0].get());
	prog->LinkProgram();

	try
	{
		// Load objects
		for(auto& objJson : j["object"])
		{
			//id, name, path, transform(position, rotation, scale -> {x, y, z})
			if(RenderObject* obj = scene->AddObject(prog, objJson["path"].get<std::string>()))
			{
				obj->Name = objJson["name"].get<std::string>();
				obj->Transform->Position = objJson["transform"]["position"].get<glm::vec3>();
				obj->Transform->Rotation = objJson["transform"]["rotation"].get<glm::vec3>();
				obj->Transform->Scale = objJson["transform"]["scale"].get<glm::vec3>();


			}

		}


	}
	catch(...)
	{

	}


	return true;
}


void glm::to_json(json& j, const vec3& vec)
{
	j["x"] = vec.x;
	j["y"] = vec.y;
	j["z"] = vec.z;
}

void glm::from_json(const json& j, glm::vec3& vec)
{
	j.at("x").get_to(vec.x);
	j.at("y").get_to(vec.y);
	j.at("z").get_to(vec.z);
}