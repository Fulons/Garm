#pragma once
#include "Widget.h"
#include <functional>

namespace garm{ namespace gui{

	class Window;

	class Header : public Widget {
		graphics::GUISprite m_backgroundSprite;
	public:
		Header(Window* parent, glm::ivec2 pos, glm::ivec2 size);
		virtual void Render(graphics::GUIRenderer* renderer);
	};

} }