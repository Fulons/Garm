#include "Renderable.h"
#include "MeshData.h"
#include "Shader.h"

namespace garm { namespace graphics {

	void Group::AddChild(Renderable* renderable){
		m_children.push_back(renderable);
	}

	void Group::Render(Shader* shader){
		Renderable::Render(shader);
		for (auto child : m_children)
			child->Render(shader);
	}

} }