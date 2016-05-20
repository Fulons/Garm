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

		Listener<InputListener>::AttachTo(InputHandler_M);
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

	bool GUILayer::MouseLDown(InputHandler * src, glm::ivec2 point){
		point = glm::ivec2(point.x, PROJECTION_Y_SIZE - point.y);
		for (auto i : m_windows) {
			if (i->ContainsInGlobalCoordinate(point)) {
				i->MouseLDown(point);
				return false;
			}
		}
		return true;
	}

	bool GUILayer::MouseRDown(InputHandler * src, glm::ivec2 point){
		point = glm::ivec2(point.x, PROJECTION_Y_SIZE - point.y);
		for (auto i : m_windows) {
			if (i->ContainsInGlobalCoordinate(point)) {
				i->MouseRDown(point);
				return false;
			}
		}
		return true;
	}

	bool GUILayer::MouseLUp(InputHandler * src, glm::ivec2 point){
		point = glm::ivec2(point.x, PROJECTION_Y_SIZE - point.y);
		for (auto i : m_windows) {
			if (i->ContainsInGlobalCoordinate(point)) {
				i->MouseLUp(point);
				return false;
			}
		}
		return true;
	}

	bool GUILayer::MouseRUp(InputHandler * src, glm::ivec2 point){
		point = glm::ivec2(point.x, PROJECTION_Y_SIZE - point.y);
		for (auto i : m_windows) {
			if (i->ContainsInGlobalCoordinate(point)) {
				i->MouseRUp(point);
				return false;
			}
		}
		return true;
	}

	bool GUILayer::MouseLClick(InputHandler * src, glm::ivec2 point){
		point = glm::ivec2(point.x, PROJECTION_Y_SIZE - point.y);
		for (auto i : m_windows) {
			if (i->ContainsInGlobalCoordinate(point)) {
				i->MouseLClick(point);
				return false;
			}
		}
		return true;
	}

	bool GUILayer::MouseRClick(InputHandler * src, glm::ivec2 point){
		point = glm::ivec2(point.x, PROJECTION_Y_SIZE - point.y);
		for (auto i : m_windows) {
			if (i->ContainsInGlobalCoordinate(point)) {
				i->MouseRClick(point);
				return false;
			}
		}
		return true;
	}

} }