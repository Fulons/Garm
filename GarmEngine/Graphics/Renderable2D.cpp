#include "Renderable2D.h"
#include "Shader.h"
#include "Texture.h"
#include "IndexBuffer.h"
namespace garm { namespace graphics {


	Renderable2D::Renderable2D(Mesh2D * mesh, TextureOld* texture)
	: m_mesh(mesh), m_texture(texture){

	}

	void Renderable2D::UpdateModelMatrix(){
		glm::mat4 initialTransformation(1);
		if (m_parent != nullptr) initialTransformation = m_parent->GetModelMatrix();
		glm::mat4 translate = glm::translate(initialTransformation, m_position);
		glm::mat4 rotate = glm::toMat4(m_rotation);
		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(m_scale, 1.0f));
		m_modelMatrix = translate * rotate * scale;
		m_changed = false;
	}

	void Renderable2D::Render(Shader * shader){
		if (m_texture) {
			m_texture->Bind(0);
		}
		if (m_changed) {
			UpdateModelMatrix();
		}
		shader->SetUniform("m", m_modelMatrix);
		m_mesh->Render();
	}

	const glm::mat4 & Renderable2D::GetModelMatrix()
	{
		if (m_changed) {
			UpdateModelMatrix();
		}
		return m_modelMatrix;
	}

	Renderable2D* Renderable2D::MakeDefaultRenderable(TextureOld* texture, glm::vec4 color){
		Vertex vertex[] = {
			{
				glm::vec3(0.0f, 0.0f, 0.0f),
				color,
				glm::vec2(0.0f, 1.0f)
			},{
				glm::vec3(1.0f, 0.0f, 0.0f),
				color,
				glm::vec2(1.0f, 1.0f)
			},{
				glm::vec3(1.0f, 1.0f, 0.0f),
				color,
				glm::vec2(1.0f, 0.0f)
			},{
				glm::vec3(0.0f, 1.0f, 0.0f),
				color,
				glm::vec2(0.0f, 0.0f)
			}
		};
		GLushort indices[] = {
			0, 1, 2,
			0, 2, 3
		};	

		Mesh2D* mesh = new Mesh2D(vertex, 4, new IndexBuffer(indices, 6), true);
		return new Renderable2D(mesh, texture);
	}

	void Renderable2D::setPosition(const glm::vec3 & pos){
		m_position = pos;
		TranslationChanged();
	}

	void Renderable2D::move(const glm::vec3 & dir){
		m_position += dir;
		TranslationChanged();
	}

	void Renderable2D::setRotation(const glm::quat & rot){
		m_rotation = rot;
		TranslationChanged();
	}

	void Renderable2D::rotate(const glm::quat & rot){
		m_rotation *= rot;
		TranslationChanged();
	}

	void Renderable2D::setScale(const glm::vec2& scale){
		m_scale = scale;
		TranslationChanged();
	}

	void Renderable2D::addScale(const glm::vec2& scale){
		m_scale += scale;
		TranslationChanged();
	}

	void Renderable2D::scale(const glm::vec2& scale){
		m_scale *= scale;
		TranslationChanged();
	}

	void Renderable2D::scale(float scale){
		m_scale *= scale;
		TranslationChanged();
	}

} }