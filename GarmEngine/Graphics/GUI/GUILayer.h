#pragma once
#include "../Layer.h"
#include "Window.h"
#include "../../Context/InputHandler.h"

#define PROJECTION_X_SIZE 800
#define PROJECTION_Y_SIZE 600

namespace garm { namespace graphics {

	class Shader;
	class GUIRenderer;

	class GUILayer : public Layer, public event::Listener<InputListener>  {
	protected:
		glm::mat4 m_projectionMatrix;
		std::vector<gui::Window*> m_windows;
		GUIRenderer* m_renderer;
		Shader* m_shader;
	public:
		Shader* m_fontShader;
		inline Shader* GetShader() { return m_shader; }
		GUILayer(glm::mat4 projection);
		void AddWindow(gui::Window* window);
		virtual void OnRender() override;

		virtual bool MouseLDown(InputHandler* src, glm::ivec2 point) override;
		virtual bool MouseRDown(InputHandler* src, glm::ivec2 point) override;

		virtual bool MouseLUp(InputHandler* src, glm::ivec2 point) override;
		virtual bool MouseRUp(InputHandler* src, glm::ivec2 point) override;

		virtual bool MouseLClick(InputHandler* src, glm::ivec2 point) override;
		virtual bool MouseRClick(InputHandler* src, glm::ivec2 point) override;
	};

} }