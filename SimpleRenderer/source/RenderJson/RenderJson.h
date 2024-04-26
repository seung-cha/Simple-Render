#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <nlohmann/json.hpp>

#include "RenderShaderProgram/ShaderProgramData.h"

using json = nlohmann::json;

namespace SimpleRender
{
	class RenderObject;
	class RenderScene;

	void to_json(json& j, const RenderObject* const& obj);
	/// <summary>
	/// Get the heap-allocated render object from json.
	/// Assumes the json file is valid.
	/// </summary>
	/// <param name="j"></param>
	/// <returns>RenderObject created using the new keyword</returns>
	ShaderProgramData* InstantiateShaderProgramDataFromJson(const json& j, const RenderScene* const& scene);
	bool LoadSceneFromJson(const json& j, RenderScene* const& scene);



	void to_json(json& j, const RenderScene* const& scene);
	void to_json(json& j, ShaderProgramData::RefType const& type);
	
	void to_json(json& j, const ShaderProgramData* const& data);
	void to_json(json& j, const ShaderDataInt* const& data);
	void to_json(json& j, const ShaderDataFloat* const& data);
	void to_json(json& j, const ShaderDataVec2* const& data);
	void to_json(json& j, const ShaderDataVec3* const& data);

	void from_json(const json& j, ShaderProgramData::RefType& type);

}
	

namespace glm
{
	void to_json(json& j, const glm::vec3& vec);
	void from_json(const json& j, glm::vec3& vec);

	void to_json(json& j, const glm::vec2& vec);
	void from_json(const json& j, glm::vec2& vec);



}