#include "Widget.h"

using garm::graphics::GUIRenderer;

namespace garm { namespace gui {

	Widget::Widget(const Widget * parent)
	: m_parent(parent), m_visible(GUI_WIDGET_STD_VISIBILITY), m_enabled(GUI_WIDGET_STD_ENABLE),
	m_focused(GUI_WIDGET_STD_FOCUSE), m_mouseFocus(GUI_WIDGET_STD_MOUSEFOCUSE){}
	
	Widget::Widget(const Widget * parent, glm::ivec2 pos, glm::ivec2 size)
	: m_parent(parent), m_pos(pos), m_size(size),
	m_visible(GUI_WIDGET_STD_VISIBILITY), m_enabled(GUI_WIDGET_STD_ENABLE),
	m_focused(GUI_WIDGET_STD_FOCUSE), m_mouseFocus(GUI_WIDGET_STD_MOUSEFOCUSE){}

	Widget::~Widget(){

	}

	void Widget::AddChild(Widget * child){
		m_children.push_back(child);
	}

	void Widget::RemoveChild(Widget * child) {
		for (auto it = m_children.begin(); it != m_children.end(); it++) {
			if (*it == child) {
				m_children.erase(it);
				return;
			}
		}
	}

	bool Widget::Contains(glm::ivec2 point)
	{
		if (point.x < m_pos.x) return false;
		if (point.x > m_pos.x + m_size.x) return false;
		if (point.y < m_pos.y) return false;
		if (point.y > m_pos.y + m_size.y) return false;
		return true;
	}

	void Widget::Render(GUIRenderer* renderer){
		for (auto child : m_children) {
			if (child->Visible())
				child->Render(renderer);
		}
	}
} }