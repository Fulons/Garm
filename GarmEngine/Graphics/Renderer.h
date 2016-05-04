#pragma once
#include "Renderable2D.h"
#include <vector>

namespace garm { namespace graphics {

	class Renderer {

	public:
		virtual void Render(Shader* shader) = 0;
	};

	class Simple2DRenderer : public Renderer {
		std::vector<Renderable2D*> m_renderables;
	public:
		void Begin();
		void Submit(Renderable2D* renderable);
		virtual void Render(Shader* shader) override;
	};

} }