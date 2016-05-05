#pragma once

#include "Renderable2D.h"

namespace garm { namespace graphics {

	class Group2D : public Renderable2D {
		std::vector<Renderable2D*> m_renderables;
		virtual void TranslationChanged() override;
	public:
		Group2D(Mesh2D* mesh, Texture* texture = nullptr) : Renderable2D(mesh, texture){}
		virtual void Render(Shader* shader) override;
		virtual int GetNumRenderables() override;
		void AddRenderable(Renderable2D* renderable);
		void RemoveRenderable(Renderable2D* renderable);
	};

} }