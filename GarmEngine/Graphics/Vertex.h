#pragma once
#include <glm/glm.hpp>

namespace garm {
	namespace graphics {

		struct Vertex {
			Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2&UV)
				: position(position), color(color), UV(UV) {}
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 UV;
		};

} }