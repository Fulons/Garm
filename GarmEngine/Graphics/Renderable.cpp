#include "Renderable.h"
#include "MeshData.h"
#include "Shader.h"

namespace garm { namespace graphics {

	void Group::AddChild(Renderable* renderable, bool parentRendering){
		m_children.push_back(std::make_pair(renderable, parentRendering));
	}

	void Group::Render(Shader* shader){
		for (auto child : m_children)
			if(child.second) child.first->Render(shader);
	}

} }