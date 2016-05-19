#include "header.h"
#include "Button.h"
#include "Window.h"
#include "../FontRenderable.h"

namespace garm { namespace gui {

	Header::Header(Window* parent, glm::ivec2 pos, glm::ivec2 size)
	: Widget(parent, pos, size){

		AddChild(new Button(this,
			glm::ivec2(size.x - GUI_WINDOW_HEADER_HEIGHT + BUTTON_PADDING, BUTTON_PADDING),
			glm::ivec2(GUI_WINDOW_HEADER_HEIGHT - BUTTON_PADDING * 2, GUI_WINDOW_HEADER_HEIGHT - BUTTON_PADDING * 2),
			[parent]() { parent->Close(); },
			graphics::GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_CLOSE));

		AddChild(new Button(this,
			glm::ivec2(size.x - (GUI_WINDOW_HEADER_HEIGHT - BUTTON_PADDING) * 2, BUTTON_PADDING),
			glm::ivec2(GUI_WINDOW_HEADER_HEIGHT - BUTTON_PADDING * 2, GUI_WINDOW_HEADER_HEIGHT - BUTTON_PADDING * 2),
			[parent]() { parent->ToggleHeaderOnly(); },
			graphics::GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_TOGGLEHONLY));

		m_textRenderable = new graphics::FontRenderable(parent->GetName(), GUI_WINDOW_HEADER_HEIGHT, { glm::vec4(0.8f, 0.8f, 0.8f, 1.0f) });

		m_backgroundSprite.size = m_size;
		m_backgroundSprite.color = glm::vec4(1.0f, 0.58f, 0.93f, 1.0f);
		m_backgroundSprite.type = graphics::GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP_INVERSE;
	}

	void Header::Render(graphics::GUIRenderer * renderer){
		if (!m_visible) return;
		renderer->PushPosition(m_pos);
		renderer->AddSprite(m_backgroundSprite);
		renderer->PushPosition(glm::ivec2(3, 5));
		renderer->AddText(m_textRenderable);
		renderer->PopPosition();
		Widget::Render(renderer);
		renderer->PopPosition();
	}

} }