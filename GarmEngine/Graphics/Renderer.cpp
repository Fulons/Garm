#include "Renderer.h"

namespace garm { namespace graphics {

	void Simple2DRenderer::Begin(){
		m_renderables.clear();
	}

	void Simple2DRenderer::Submit(Renderable2D * renderable){
		m_renderables.push_back(renderable);
	}

	void Simple2DRenderer::Render(Shader* shader){
		for (auto i : m_renderables) {
			i->Render(shader);
		}
	}



} }