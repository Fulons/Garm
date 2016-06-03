#pragma once
#include "Widget.h"
#include <functional>

namespace garm { namespace gui{

	class Menu : public Widget {
		std::function<void(unsigned)> m_callback;
		const std::vector<std::string>& m_items;
		graphics::GUISprite m_backgroundSprite;
	public:
		Menu(Widget* parent, glm::ivec2 pos, glm::ivec2 size, const std::vector<std::string>& strings);
		void SetCallBack(const std::function<void(unsigned)>& callback);
		virtual void Render(graphics::GUIRenderer* renderer) override;
	};

} }