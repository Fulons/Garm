#include "TextField.h"
#include "../FontRenderable.h"

namespace garm { namespace gui {

	TextField::TextField(Widget * parent, glm::ivec2 pos, glm::ivec2 size)
	: Widget(parent, pos, size){
		m_fontRenderable = new graphics::FontRenderable("", 15, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) });
		m_backgroundSprite.size = size;
		m_backgroundSprite.color = glm::vec4(0.3f, 0.0f, 0.7f, 1.0f);
		m_backgroundSprite.type = graphics::GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP_INVERSE;
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

	void TextField::SetText(std::string str){
		m_string = str;
		m_fontRenderable->SetString(str);
		m_fontRenderable->RefreshBuffer();
	}

} }