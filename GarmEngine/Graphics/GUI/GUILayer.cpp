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
		
		m_fontShader = new Shader("Shaders/vFont.shader", "Shaders/fFont.shader");
		m_fontShader->Use();
		m_fontShader->SetUniform("p", projection);
		m_fontShader->SetUniform("m", glm::mat4(1));
		m_fontShader->SetUniform("t", 0);

		m_renderer = new GUIRenderer;
	}

	void GUILayer::AddWindow(Window* window){
		m_windows.push_back(window);
	}

	void GUILayer::OnRender(){
		glDepthRange(1000, 0);
		m_shader->Use();
		m_renderer->Begin();
		for (auto window : m_windows) {
			window->Render(m_renderer);
		}
		m_renderer->End();

		m_fontShader->Use();
		m_renderer->RenderFont(m_fontShader);
		glDepthRange(-1, 1);
	}

} }