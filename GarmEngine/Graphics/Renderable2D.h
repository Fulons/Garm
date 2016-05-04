#pragma once
#include "Mesh2D.h"
#include "../Math.h"
#include <vector>

namespace garm { namespace graphics {

	class Shader;

	//TODO: transformation to be moved to its own component class when
	//entity/component system is in
	class Renderable2D {
		Mesh2D* m_mesh;
		glm::vec3 m_position;
		glm::quat m_rotation = glm::quat(glm::vec3(0));
		glm::vec2 m_scale = glm::vec2(1, 1);
		glm::mat4 m_modelMatrix = glm::mat4(1);
		bool m_changed = true;
		Renderable2D* m_parent = nullptr;
		friend class Group2D;
		void UpdateModelMatrix();
	protected:
		virtual void TranslationChanged() { m_changed = true; }
	public:
		Renderable2D(Mesh2D* mesh);
		virtual void Render(Shader* shader);
		virtual int GetNumRenderables() { return 1; }
	virtual const glm::mat4& GetModelMatrix();
		
		void setPosition(const glm::vec3& pos);
		void move(const glm::vec3& dir);
		void setRotation(const glm::quat& rot);
		void rotate(const glm::quat& rot);
		void setScale(const glm::vec2& scale);
		void addScale(const glm::vec2& scale);
		void scale(const glm::vec2& scale);
		void scale(float scale);
	};

} }