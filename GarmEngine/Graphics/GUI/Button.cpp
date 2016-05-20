#include "Button.h"

namespace garm{namespace gui{

	Button::Button(const Widget * parent, glm::ivec2 pos, glm::ivec2 size, const std::function<void()> &callBack, graphics::TextureFragmentType type)
	: Widget(parent, pos, size), m_callback(callBack){
		m_sprite.size = size;
		m_sprite.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_sprite.type = type;
	}

	void Button::Render(graphics::GUIRenderer * renderer){
		if (!m_visible) return;
		renderer->PushPosition(m_pos);
		renderer->AddSprite(m_sprite);
		Widget::Render(renderer);
		renderer->PopPosition();
	}

	bool Button::MouseLClick(glm::ivec2 point){
		m_callback();
		return true;
	}

} }