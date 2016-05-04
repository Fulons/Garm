#include "Group2D.h"


namespace garm { namespace graphics {

	void Group2D::TranslationChanged(){
		for (auto renderable : m_renderables) {
			renderable->TranslationChanged();
		}
		Renderable2D::TranslationChanged();
	}

	void Group2D::Render(Shader * shader){			
		Renderable2D::Render(shader);

		for (auto renderable : m_renderables)
			renderable->Render(shader);
	}
	
	int Group2D::GetNumRenderables(){
		int ret = 1;
		for (auto renderable : m_renderables) {
			ret += renderable->GetNumRenderables();
		}
		return ret;
	}

	void Group2D::AddRenderable(Renderable2D* renderable){
		renderable->m_parent = this;
		m_renderables.push_back(renderable);
	}

	void Group2D::RemoveRenderable(Renderable2D * renderable){
		for (auto r = m_renderables.begin(); r != m_renderables.end(); r++) {
			if (*r == renderable) {
				m_renderables.erase(r);
				break;
			}
		}
	}

} }