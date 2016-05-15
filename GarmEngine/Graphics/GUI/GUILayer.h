#pragma once
#include "../Layer.h"
#include "Window.h"


namespace garm { namespace graphics {

	class Shader;

	class GUILayer : public Layer {
	protected:
		Shader* m_shader;
		std::vector<gui::Window*> m_windows;
	public:
		void AddWindow(gui::Window* window);
		virtual void OnRender() override;
	};

} }