#include "Menu.h"

namespace garm { namespace gui{

	Menu::Menu(Widget * parent, glm::ivec2 pos, glm::ivec2 size, const std::vector<std::string>& strings)
	: Widget(parent, pos, size), m_items(strings){

	}

} }