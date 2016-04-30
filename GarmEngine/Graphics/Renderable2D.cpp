#include "Renderable2D.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace garm { namespace graphics {

	Renderable2D::Renderable2D(Mesh2D * mesh){

	}

	void Renderable2D::Render(Shader * shader){

		glm::mat4 scale = glm::scale(glm::mat4_cast(m_rotation), glm::vec3(m_scale, 0.0f));
		glm::mat4 trs = glm::translate(scale, glm::vec3(m_position, 0.0f));
		shader->SetUniform("m", trs);
		m_mesh->Render();
	}

} }