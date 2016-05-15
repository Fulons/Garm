#pragma once
#include "../Math.h"
#include <vector>
#include <utility>

namespace garm { namespace graphics {

	class Shader;

	class Renderable {
	protected:
		glm::mat4 m_modelMatrix = glm::mat4(1);
		Renderable* m_parent = nullptr;
	public:
		virtual void Render(Shader* shader) {}
		void UpdateModelMatrix(glm::mat4 mm) { m_modelMatrix = mm; }
		const glm::mat4& GetModelMatrix() {
			if(m_parent == nullptr) return m_modelMatrix;
			return m_parent->GetModelMatrix() * m_modelMatrix;
		}
	};

	class Group : public Renderable {
		std::vector<std::pair<Renderable*, bool>> m_children;
	public:
		void AddChild(Renderable* renderable, bool parentRendering = true);
		virtual void Render(Shader* shader) override;
		//doubt this is needed
		//void RemoveChild(Renderable* renderable);
	};
} }
