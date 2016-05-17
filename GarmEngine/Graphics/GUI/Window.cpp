#include "Window.h"
#include "Button.h"
#include "../Renderable.h"
#include "../FontRenderable.h"
#include "header.h"

using garm::graphics::Group;
using garm::graphics::FontRenderable;
using garm::graphics::GUIRenderer;

namespace garm { namespace gui {

	Window::Window(std::string name, glm::ivec2 pos, glm::ivec2 size, unsigned flags)
	: Widget(nullptr, pos, size), m_name(name), m_flags(flags){
		
		if (IS_FLAG_SET(GUI_WINDOW_HEADER, m_flags)) {
			m_header = new Header(this, glm::ivec2(0, m_size.y - GUI_WINDOW_HEADER_HEIGHT), glm::ivec2(m_size.x, GUI_WINDOW_HEADER_HEIGHT));
			AddChild(m_header);
		}
		m_backgroundSprite.size = m_size;
		m_backgroundSprite.type = graphics::GUI_TEXTURE_FRAGMENT_TYPE_COLOR;
		m_backgroundSprite.color = glm::vec4(0.39f, 0.58f, 0.93f, 1.0f);
	}

	void Window::Close(){
		m_enabled = false;	//TODO: maybe the whole window should be destroyed? will see in the future
	}

	void Window::ToggleHeaderOnly(){
		m_headerOnly = !m_headerOnly;
	}

	void Window::Render(GUIRenderer* renderer){
		if (!m_visible) return;

		renderer->PushPosition(m_pos);

		if (!m_headerOnly) {
			renderer->AddSprite(m_backgroundSprite);
			Widget::Render(renderer);
		}
		else m_header->Render(renderer);

		renderer->PopPosition();
	}

} }