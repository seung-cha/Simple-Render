#pragma once

#include <glm/glm.hpp>


namespace SimpleRender
{
	struct RenderVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texturePosition;
		glm::vec3 tangent;
		glm::vec3 biTangent;

	};
}
