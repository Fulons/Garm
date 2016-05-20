#pragma once
#include "Widget.h"
#include <functional>

#define BUTTON_PADDING 2
#define BUTTON_XPADDING 2
#define BUTTON_YPADDING 6

namespace garm{
	namespace graphics { class FontRenderable; }
	namespace gui{

	class Window;

	class Header : public Widget {
		graphics::GUISprite m_backgroundSprite;
		graphics::FontRenderable* m_textRenderable;
		bool m_dragMode = false;
	public:
		Header(Window* parent, glm::ivec2 pos, glm::ivec2 size);
		virtual void Render(graphics::GUIRenderer* renderer);
		virtual bool MouseLDown(glm::ivec2 point) override;
		virtual bool MouseLUp(glm::ivec2 point) override;
		virtual bool MouseMove(glm::ivec2 distance) override;
	};

} }