#include "header.h"
#include "Button.h"
#include "Window.h"

namespace garm { namespace gui {

	Header::Header(Window* parent, glm::ivec2 pos, glm::ivec2 size)
	: Widget(parent, pos, size){

		AddChild(new Button(this,
			glm::ivec2(size.x - size.y - 1, 1),
			glm::ivec2(size.y - 2, size.y - 2),
			[parent]() { parent->Close(); },
			graphics::GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_CLOSE));

		AddChild(new Button(this,
			glm::ivec2(size.x - 2 * (size.y - 1), 1),
			glm::ivec2(size.y - 2, size.y - 2),
			[parent]() { parent->ToggleHeaderOnly(); },
			graphics::GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_TOGGLEHONLY));

		m_backgroundSprite.size = m_size;
		m_backgroundSprite.color = glm::vec4(1.0f, 0.58f, 0.93f, 1.0f);
		m_backgroundSprite.type = graphics::GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP;
	}

	void Header::Render(graphics::GUIRenderer * renderer){
		if (!m_visible) return;
		renderer->PushPosition(m_pos);
		renderer->AddSprite(m_backgroundSprite);
		Widget::Render(renderer);
		renderer->PopPosition();
	}

} }