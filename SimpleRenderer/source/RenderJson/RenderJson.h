#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <nlohmann/json.hpp>


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
	RenderObject* InstantiateRenderObjectFromJson(const json& j);
	bool LoadSceneFromJson(const json& j, RenderScene* const& scene);



	void to_json(json& j, const RenderScene* const& scene);

}
	

namespace glm
{
	void to_json(json& j, const glm::vec3& vec);
	void from_json(const json& j, glm::vec3& vec);
}