#pragma once
#include "../Layer.h"
#include "Window.h"


namespace garm { namespace graphics {

	class Shader;
	class GUIRenderer;

	class GUILayer : public Layer {
	protected:
		glm::mat4 m_projectionMatrix;
		std::vector<gui::Window*> m_windows;
		GUIRenderer* m_renderer;
	public:
		Shader* m_shader;
		GUILayer(glm::mat4 projection);
		void AddWindow(gui::Window* window);
		virtual void OnRender() override;
	};

} }