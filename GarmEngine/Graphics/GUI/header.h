#pragma once
#include "Widget.h"
#include <functional>

#define BUTTON_PADDING 2
#define BUTTON_XPADDING 2
#define BUTTON_YPADDING 6

namespace garm{ namespace gui{

	class Window;

	class Header : public Widget {
		graphics::GUISprite m_backgroundSprite;
	public:
		Header(Window* parent, glm::ivec2 pos, glm::ivec2 size);
		virtual void Render(graphics::GUIRenderer* renderer);
	};

} }