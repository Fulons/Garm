#pragma once
#include "Widget.h"
#include "../../Context/InputHandler.h"

namespace garm {
	namespace graphics { class FontRenderable; }
	namespace gui {

	class TextField : public Widget {
	protected:
		std::string m_string;
		graphics::GUISprite m_backgroundSprite;
		graphics::FontRenderable* m_fontRenderable;
	public:
		TextField(Widget* parent, glm::ivec2 pos, glm::ivec2 size);
		virtual void Render(graphics::GUIRenderer* renderer) override;
		virtual void SetText(std::string str);
	};

} }