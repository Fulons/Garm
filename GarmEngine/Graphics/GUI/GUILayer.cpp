#include "GUILayer.h"
#include "GUIRenderer.h"
#include "../Shader.h"

using garm::gui::Window;


namespace garm { namespace graphics{

	GUILayer::GUILayer(glm::mat4 projection)
	: m_projectionMatrix(projection){
		m_shader = new Shader("Shaders/v.shader", "Shaders/f.shader");
		m_shader->Use();
		m_shader->SetUniform("p", projection);
		m_shader->SetUniform("m", glm::mat4(1));
		m_shader->SetUniform("t", 0);
		m_renderer = new GUIRenderer;
	}

	void GUILayer::AddWindow(Window* window){
		m_windows.push_back(window);
	}

	void GUILayer::OnRender(){
		m_shader->Use();
		//m_shader->SetUniform("p", m_projectionMatrix);
		//m_shader->SetUniform("m", glm::mat4(1));
		//m_shader->SetUniform("t", 0);
		m_renderer->Begin();
		for (auto window : m_windows) {
			window->Render(m_renderer);
		}
		m_renderer->End();
	}

} }