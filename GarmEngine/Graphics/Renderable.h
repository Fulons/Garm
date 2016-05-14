#pragma once
#include "../Math.h"
#include <vector>

namespace garm { namespace graphics {

	class Shader;

	class Renderable {
	protected:
		glm::mat4 m_modelMatrix;
		bool m_modelChanged = true;
		Renderable* m_parent = nullptr;
	public:
		virtual void Render(Shader* shader) {}
	};

	class Group : public Renderable {
		std::vector<Renderable*> m_children;
	public:
		void AddChild(Renderable* renderable);
		virtual void Render(Shader* shader) override;
		//doubt this is needed
		//void RemoveChild(Renderable* renderable);
	};
} }
