#pragma once
#include "../../Math.h"
#include "GUIRenderer.h"
#include "Event.h"
#include <string>
#include <vector>

#define GUI_WIDGET_STD_VISIBILITY	true
#define GUI_WIDGET_STD_ENABLE		true
#define GUI_WIDGET_STD_FOCUS		false
#define GUI_WIDGET_STD_MOUSEFOCUS	false
#include <iostream>
namespace garm { namespace gui {

	class Widget;

	class WidgetListener {
	public:
		typedef Widget notifier_type;		
		virtual bool MouseClick(Widget* src, glm::ivec2 pos) { return true; }
	};

	//class ListenListener : public event::Listener<WidgetListener> {
	//public:
	//	void foo(Widget* e) { AttachTo((event::Notifier<WidgetListener>*)e); }
	//	virtual void Widget_Event(Widget* src, int i) override{
	//		std::cout << "Moo " << std::endl;
	//	}
	//};

	class Widget : public event::Notifier<WidgetListener>, public event::Listener<WidgetListener> {
	protected:
		const Widget* m_parent = nullptr;
		bool m_visible, m_enabled;
		bool m_focused, m_mouseFocus;
		std::vector<Widget*> m_children;
		glm::ivec2 m_pos, m_size;
	public:
		//virtual void Widget_Event(Widget* src, int data) override {std::cout << "Wof " << std::endl;}
		Widget(const Widget* parent);
		Widget(const Widget* parent, glm::ivec2 pos, glm::ivec2 size);
		Widget& operator=(const Widget& o){}
		virtual ~Widget(){}
		void AddChild(Widget* child);
		void RemoveChild(Widget* child);
		void SetPosition(glm::ivec2 pos) { m_pos = pos; }
		void SetSize(glm::ivec2 size) { m_size = size; }

		bool Visible() { return m_visible; Notify(&WidgetListener::MouseClick, glm::ivec2(2,2)); }
		bool Enabled() { return m_enabled; }
		bool Focused() { return m_focused; }
		bool MouseFocus() { return m_mouseFocus; }

		virtual bool Contains(glm::ivec2 point);
		virtual void Render(graphics::GUIRenderer* renderer);
	};

} }