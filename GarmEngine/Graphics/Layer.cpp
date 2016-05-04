#include "Layer.h"
#include "Renderer.h"
#include "Shader.h"

namespace garm { namespace graphics {


	Simple2DLayer::Simple2DLayer(const glm::mat4 & projectionMatrix)
	: m_projectionMatrix(projectionMatrix), m_renderer(new Simple2DRenderer()),
	m_shader(new Shader("Shaders/vShader.shader", "Shaders/fShader.shader")){
		m_shader->Use();
		m_shader->SetUniform("p", m_projectionMatrix);
	}
	Simple2DLayer::~Simple2DLayer(){
		delete m_renderer;
		delete m_shader;
	}

	void Simple2DLayer::AddRenderable(Renderable2D * renderable){
		m_Renderables.push_back(renderable);
	}

	void Simple2DLayer::OnRender(){
		m_shader->Use();
		for (Renderable2D* renderable : m_Renderables) {
			renderable->Render(m_shader);
		}
	}
}}