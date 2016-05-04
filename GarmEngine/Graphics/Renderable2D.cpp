#include "Renderable2D.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace garm { namespace graphics {

	Renderable2D::Renderable2D(Mesh2D * mesh)
	: m_mesh(mesh){

	}

	void Renderable2D::Render(Shader * shader){
		if (m_changed) {
			glm::mat4 translate = glm::translate(glm::mat4(1), m_position);
			glm::mat4 translateScale = glm::scale(translate, glm::vec3(m_scale, 1.0f));
			m_modelMatrix = glm::mat4_cast(m_rotation) * translateScale;
			m_changed = false;
		}
		shader->SetUniform("m", m_modelMatrix);
		m_mesh->Render();
	}

	void Renderable2D::setPosition(const glm::vec3 & pos){
		m_position = pos;
		m_changed = true;
	}

	void Renderable2D::move(const glm::vec3 & dir){
		m_position += dir;
		m_changed = true;
	}

	void Renderable2D::setRotation(const glm::quat & rot){
		m_rotation = rot;
		m_changed = true;
	}

	void Renderable2D::rotate(const glm::quat & rot){
		m_rotation *= rot;
		m_changed = true;
	}

	void Renderable2D::setScale(const glm::vec2& scale){
		m_scale = scale;
		m_changed = true;
	}

	void Renderable2D::addScale(const glm::vec2& scale){
		m_scale += scale;
		m_changed = true;
	}

	void Renderable2D::scale(const glm::vec2& scale){
		m_scale *= scale;
		m_changed = true;
	}

	void Renderable2D::scale(float scale){
		m_scale *= scale;
		m_changed = true;
	}

} }