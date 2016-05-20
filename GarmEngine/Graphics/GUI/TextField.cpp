#include "TextField.h"
#include "../FontRenderable.h"

namespace garm { namespace gui {

	TextField::TextField(Widget * parent, glm::ivec2 pos, glm::ivec2 size)
	: Widget(parent, pos, size){
		m_fontRenderable = new graphics::FontRenderable("", 15, { glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) });
		m_backgroundSprite.size = size;
		m_backgroundSprite.color = glm::vec4(0.9f, 0.0f, 0.5f, 1.0f);
		m_backgroundSprite.type = graphics::GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP;
	}

	void TextField::Render(graphics::GUIRenderer * renderer){
		if (!m_visible) return;
		renderer->PushPosition(m_pos);
		renderer->AddSprite(m_backgroundSprite);
		renderer->PushPosition(glm::ivec2(3, 5));
		renderer->AddText(m_fontRenderable);
		renderer->PopPosition();
		Widget::Render(renderer);
		renderer->PopPosition();
	}

	bool TextField::MouseLClick(glm::ivec2 point){
		InputHandler_M->TakeInUnicode([this](unsigned c) { this->UnicodeIn(c); }, this);
		return true;
	}

	void TextField::UnicodeIn(unsigned c){
		//the first 32 values in the ascii table is no meant for printing...
		//not realy space either but havnt been bothered to solve skipping it in the fontRenderable buffer creation yet.
		if (c < 32) {
			if (c == 8) { //backspace
				
			}
		}
	}


} }