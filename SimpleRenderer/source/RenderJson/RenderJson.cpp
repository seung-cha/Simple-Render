#include "RenderJson.h"

#include "RenderObject/RenderObject.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"

#include "RenderDeferredRender/RenderDeferredRender.h"
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

	// Store the uniform data in deferredRender 
	for(auto& data : *scene->DeferredRender->ShaderProgram->UniformData)
	{
		j["uniform"] += data;
	}

}


void SimpleRender::to_json(json& j, ShaderProgramData::RefType const& type)
{
	j = static_cast<typename std::underlying_type<ShaderProgramData::RefType>::type>(type);
}

void SimpleRender::from_json(const json& j, ShaderProgramData::RefType& type)
{
	
	int i = j.get<int>();
	type = static_cast<ShaderProgramData::RefType>(i);
}



void SimpleRender::to_json(json& j, const ShaderProgramData* const& data)
{
	
	if(const ShaderDataInt* const o = dynamic_cast<const ShaderDataInt* const>(data))
	{
		j = o;
	}
	else if(const ShaderDataFloat* const o = dynamic_cast<const ShaderDataFloat* const>(data))
	{
		j = o;
	}
	else if(const ShaderDataVec2* const o = dynamic_cast<const ShaderDataVec2* const>(data))
	{
		j = o;
	}
	else if(const ShaderDataVec3* const o = dynamic_cast<const ShaderDataVec3* const>(data))
	{
		j = o;
	}

}


void SimpleRender::to_json(json& j, const ShaderDataInt* const& data)
{
	j["type"] = "int";
	j["name"] = data->name;
	j["reftype"] = data->ReferenceType;

	if(!data->ReadOnly)
	{
		j["data"] = *static_cast<int*>(data->data);
	}
}

void SimpleRender::to_json(json& j, const ShaderDataFloat* const& data)
{
	j["type"] = "float";
	j["name"] = data->name;
	j["reftype"] = data->ReferenceType;

	if(!data->ReadOnly)
	{
		j["data"] = *static_cast<float*>(data->data);
	}
}

void SimpleRender::to_json(json& j, const ShaderDataVec2* const& data)
{
	j["type"] = "vec2";
	j["name"] = data->name;
	j["reftype"] = data->ReferenceType;

	if(!data->ReadOnly)
	{
		j["data"] = *static_cast<glm::vec2*>(data->data);
	}
}

void SimpleRender::to_json(json& j, const ShaderDataVec3* const& data)
{
	j["type"] = "vec3";
	j["name"] = data->name;

	j["reftype"] = data->ReferenceType;

	if(!data->ReadOnly)
	{
		j["data"] = *static_cast<glm::vec3*>(data->data);
	}
	else
	{
		//Must be tracking an object, get the ID instead.
		RenderObject* o = static_cast<SimpleRender::RenderObject*>(data->data);
		if(o)
		{
			j["data"] = o->ID;
		}
		else
		{
			// Indicate reference is broken
			j["data"] = -1;
		}
	}
}





SimpleRender::ShaderProgramData* SimpleRender::InstantiateShaderProgramDataFromJson(const json& j, const RenderScene* const& scene)
{
	std::string t = j["type"].get<std::string>();

	if(t == "int")
	{
		SimpleRender::ShaderDataInt* v = new SimpleRender::ShaderDataInt();
		v->name = j["name"].get<std::string>();
		v->ReferenceType = j["reftype"];


		switch(v->ReferenceType)
		{
		case ShaderProgramData::RefType::RunTimei:
			v->ToVariable(&scene->Application->Status->Timei);
			break;
			
		case ShaderProgramData::RefType::LeftClickCont:
			v->ToVariable(&scene->Application->Status->Mouse->LeftClick);
			break;

		case ShaderProgramData::RefType::RightClickCont:
			v->ToVariable(&scene->Application->Status->Mouse->RightClick);
			break;

		default:
			v->ToConstant();
			*(static_cast<int*>(v->data)) = j["data"].get<int>();
		}

		return v;
	}
	else if(t == "float")
	{
		SimpleRender::ShaderDataFloat* v = new SimpleRender::ShaderDataFloat();
		v->name = j["name"].get<std::string>();
		v->ReferenceType = j["reftype"];

		switch(v->ReferenceType)
		{
		case ShaderProgramData::RefType::RunTimef:
			v->ToVariable(&scene->Application->Status->Timef);
			break;

		case ShaderProgramData::RefType::AspectRatio:
			v->ToVariable(&scene->Application->Status->AspectRatio);
			break;
		case ShaderProgramData::RefType::AspectRatioFixed:
			v->ToVariable(&scene->Application->Status->FixedAspectRatio);
			break;

		default:
			v->ToConstant();
			*(static_cast<float*>(v->data)) = j["data"].get<float>();
		}



		return v;

	}
	else if(t == "vec2")
	{
		SimpleRender::ShaderDataVec2* v = new SimpleRender::ShaderDataVec2();
		v->name = j["name"].get<std::string>();
		v->ReferenceType = j["reftype"];


		switch(v->ReferenceType)
		{
		case ShaderProgramData::RefType::MouseDelta:
			v->ToVariable(&scene->Application->Status->Mouse->MouseDelta);
			break;

		case ShaderProgramData::RefType::MousePos:
			v->ToVariable(&scene->Application->Status->Mouse->MouseCoordinates);
			break;

		case ShaderProgramData::RefType::Resoltion:
			v->ToVariable(&scene->Application->Status->Resolution);
			break;

		case ShaderProgramData::RefType::ResolutionFixed:
			v->ToVariable(&scene->Application->Status->FixedResolution);
			break;

		default:
			v->ToConstant();
			*(static_cast<glm::vec2*>(v->data)) = j["data"];

		}
		

		return v;
	}
	else if(t == "vec3")
	{
		SimpleRender::ShaderDataVec3* v = new SimpleRender::ShaderDataVec3();
		v->name = j["name"].get<std::string>();
		v->ReferenceType = j["reftype"];

		if(v->ReferenceType == ShaderProgramData::RefType::None)
		{
			v->ToConstant();
			*static_cast<glm::vec3*>(v->data) = j["data"];
			
		}
		else
		{
			int id = j["data"].get<int>();

			if(id-1 < 0 || id-1 >= scene->SceneObjects->size())
			{
				v->ToVariable(nullptr);
			}
			else
			{
				v->ToVariable((*scene->SceneObjects)[id-1].get());
			}

		}




		return v;
	}

	return nullptr;
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


		for(auto& uniformJson : j["uniform"])
		{
			SimpleRender::ShaderProgramData* d = InstantiateShaderProgramDataFromJson(uniformJson, scene);

			if(d)
			{
				scene->DeferredRender->ShaderProgram->UniformData->push_back(d);
			}
		}


	}
	catch(...)
	{
		return false;
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


void glm::to_json(json& j, const vec2& vec)
{
	j["x"] = vec.x;
	j["y"] = vec.y;

}

void glm::from_json(const json& j, glm::vec2& vec)
{
	j.at("x").get_to(vec.x);
	j.at("y").get_to(vec.y);
}