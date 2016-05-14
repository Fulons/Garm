#pragma once

#include "../Math.h"
#include "Layer.h"
#include <vector>

namespace garm { namespace graphics{

	class Shader;
	class Renderable2D;
	class Simple2DRenderer;
	
	class Simple2DLayer : Layer {
	private:
		Shader* m_shader;
		Shader* m_fontShader;
		Simple2DRenderer* m_renderer;
		std::vector<Renderable2D*> m_renderables;
		glm::mat4 m_projectionMatrix;
	public:
		Simple2DLayer(const glm::mat4& projectionMatrix);
		~Simple2DLayer();
		Shader* GetShader() { return m_shader; }
	
		void AddRenderable(Renderable2D* renderable);
	
		virtual void OnRender();
	};

} }