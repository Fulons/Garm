#pragma once
#include "Mesh2D.h"
#include <glm/gtc/quaternion.hpp>

namespace garm { namespace graphics {

	class Shader;

	class Renderable2D {
		Mesh2D* m_mesh;
		glm::vec2 m_position;
		glm::quat m_rotation;
		glm::vec2 m_scale;
	public:
		Renderable2D(Mesh2D* mesh);
		virtual void Render(Shader* shader);

	};

} }