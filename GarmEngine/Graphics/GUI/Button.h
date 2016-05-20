#pragma once
#include "Widget.h"

#include <functional>

namespace garm { namespace gui {

	class Button : public Widget {
	protected:
		std::function<void()> m_callback;
		graphics::GUISprite m_sprite;
	public:
		Button(Widget* parent, glm::ivec2 pos, glm::ivec2 size, const std::function<void()> &callBack,  graphics::TextureFragmentType type);
		void Render(graphics::GUIRenderer* renderer) override;
		virtual bool MouseLClick(glm::ivec2 point) override;
		//So that ancestors can check if action is being caught
		//Should probably just make a different function for this kinds of check
		virtual bool MouseLDown(glm::ivec2 point) override { return false; }
	};

} }