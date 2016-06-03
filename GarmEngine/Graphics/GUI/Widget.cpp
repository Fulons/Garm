#include "Widget.h"

using garm::graphics::GUIRenderer;

namespace garm { namespace gui {

	Widget::Widget(Widget * parent)
	: m_parent(parent), m_visible(GUI_WIDGET_STD_VISIBILITY), m_enabled(GUI_WIDGET_STD_ENABLE),
	m_focused(GUI_WIDGET_STD_FOCUS), m_mouseFocus(GUI_WIDGET_STD_MOUSEFOCUS), event::Notifier<WidgetListener>(){
		if (parent != nullptr) AttachTo(parent);
	}
	
	Widget::Widget(Widget * parent, glm::ivec2 pos, glm::ivec2 size)
	: m_parent(parent), m_pos(pos), m_size(size),
	m_visible(GUI_WIDGET_STD_VISIBILITY), m_enabled(GUI_WIDGET_STD_ENABLE),
	m_focused(GUI_WIDGET_STD_FOCUS), m_mouseFocus(GUI_WIDGET_STD_MOUSEFOCUS), event::Notifier<WidgetListener>(){
		if (parent != nullptr) AttachTo(parent);
	}

	void Widget::AddChild(Widget * child){
		m_children.push_back(child);
	}

	void Widget::AddChildFront(Widget* child) {
		m_children.insert(m_children.begin(), child);
	}

	void Widget::RemoveChild(Widget * child) {
		for (auto it = m_children.begin(); it != m_children.end(); it++) {
			if (*it == child) {
				m_children.erase(it);
				return;
			}
		}
	}

	bool Widget::ContainsInParentCoordinate(glm::ivec2 point) const {
		return math::pointInRect(point, m_size, m_pos);
	}

	bool Widget::ContainsInGlobalCoordinate(glm::ivec2 point) const{
		if(m_parent == nullptr) return math::pointInRect(point, m_size, m_pos);
		else return m_parent->ContainsInGlobalCoordinate(point);
	}

	bool Widget::ContainsInLocalCoordinate(glm::ivec2 point) const{
		return math::pointInRect(point, m_size);
	}

	glm::ivec2 Widget::ParentToWidgetCoordinate(glm::ivec2 point) const{
		return point - m_parent->m_size;
	}

	glm::ivec2 Widget::GlobalToWidgetCoordinate(glm::ivec2 point) const{
		return point - GetGlobalPosition();
	}

	glm::ivec2 Widget::GetGlobalPosition() const{
		if (m_parent != nullptr) return m_parent->GetGlobalPosition() + m_pos;
		else return m_pos;
	}

	bool Widget::MouseLDown(glm::ivec2 point){
		point -= m_pos;
		for (auto i : m_children) {
			if (i->ContainsInParentCoordinate(point)) {
				if (i->MouseLDown(point)) return true;
				return true;
			}
		}
		return false;
	}

	bool Widget::MouseRDown(glm::ivec2 point){
		point -= m_pos;
		for (auto i : m_children) {
			if (i->ContainsInParentCoordinate(point))
				if (i->MouseRDown(point)) return true;
		}
		return false;
	}

	bool Widget::MouseLUp(glm::ivec2 point){
		point -= m_pos;
		for (auto i : m_children) {
			if (i->ContainsInParentCoordinate(point))
				if (i->MouseLUp(point)) return true;
		}
		return false;
	}

	bool Widget::MouseRUp(glm::ivec2 point){
		point -= m_pos;
		for (auto i : m_children) {
			if (i->ContainsInParentCoordinate(point))
				if (i->MouseRUp(point)) return true;
		}
		return false;
	}

	bool Widget::MouseLClick(glm::ivec2 point){
		point -= m_pos;
		for (auto i : m_children) {
			if (i->ContainsInParentCoordinate(point))
				if(i->MouseLClick(point)) return true;
		}
		return false;
	}

	bool Widget::MouseRClick(glm::ivec2 point){
		point -= m_pos;
		for (auto i : m_children) {
			if (i->ContainsInParentCoordinate(point))
				if (i->MouseRClick(point)) return true;
		}
		return false;
	}

	bool Widget::MouseMove(glm::ivec2 distance){
		for (auto i : m_children)
			if (!i->MouseMove(distance)) return false;
		return true;
	}

	void Widget::Render(GUIRenderer* renderer) {
		for (auto child : m_children) {
			if (child->Visible())
				child->Render(renderer);
		}
	}
} }