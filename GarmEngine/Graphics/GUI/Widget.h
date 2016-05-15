#pragma once
#include "../../Math.h"
#include <string>
#include <vector>

#define GUI_WIDGET_STD_VISIBILITY	true
#define GUI_WIDGET_STD_ENABLE		true
#define GUI_WIDGET_STD_FOCUSE		false
#define GUI_WIDGET_STD_MOUSEFOCUSE	false

namespace garm { namespace gui {

	class Widget {
	protected:
		const Widget* m_parent = nullptr;
		bool m_visible, m_enabled;
		bool m_focused, m_mouseFocus;
		std::vector<Widget*> m_children;
		glm::ivec2 m_pos, m_size;
	public:
		Widget(const Widget* parent);
		virtual ~Widget();
		void AddChild(Widget* child);
		void RemoveChild(Widget* child);
		void SetPosition(glm::ivec2 pos) { m_pos = pos; }
		void SetSize(glm::ivec2 size) { m_size = size; }

		bool Visible() { return m_visible; }
		bool Enabled() { return m_enabled; }
		bool Focused() { return m_focused; }
		bool MouseFocus() { return m_mouseFocus; }

		virtual bool Contains(glm::ivec2 point);
		virtual void Render();
	};

	

} }