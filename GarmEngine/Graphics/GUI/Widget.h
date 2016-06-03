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
	class InputHandler;
	class Widget;

	class WidgetListener {
	public:
		typedef Widget notifier_type;		
		virtual bool MinimizedToHeader(Widget* src) { return true; }
	};

	class Widget : public event::Notifier<WidgetListener>, public event::Listener<WidgetListener> {
	protected:
		Widget* m_parent = nullptr;
		bool m_visible, m_enabled;
		bool m_focused, m_mouseFocus;
		std::vector<Widget*> m_children;
		glm::ivec2 m_pos, m_size;
		Widget* GetWindow() { if (m_parent == nullptr) return this; return m_parent->GetWindow(); }
	public:
		//virtual void Widget_Event(Widget* src, int data) override {std::cout << "Wof " << std::endl;}
		Widget(Widget* parent);
		Widget(Widget* parent, glm::ivec2 pos, glm::ivec2 size);
		Widget& operator=(const Widget& o){}
		virtual ~Widget(){}
		void AddChild(Widget* child);
		void AddChildFront(Widget* child);	//inefficient should make second vector to store "queue jumpers"
		void RemoveChild(Widget* child);
		void SetPosition(glm::ivec2 pos) { m_pos = pos; }
		void SetSize(glm::ivec2 size) { m_size = size; }

		void Move(glm::ivec2 distance) { m_pos += distance; }

		bool Visible() const { return m_visible; }
		bool Enabled() const { return m_enabled; }
		bool Focused() const { return m_focused; }
		bool MouseFocus() const { return m_mouseFocus; }

		virtual bool ContainsInParentCoordinate(glm::ivec2 point) const;
		virtual bool ContainsInGlobalCoordinate(glm::ivec2 point) const;
		virtual bool ContainsInLocalCoordinate(glm::ivec2 point) const;
		virtual glm::ivec2 ParentToWidgetCoordinate(glm::ivec2 point) const;
		virtual glm::ivec2 GlobalToWidgetCoordinate(glm::ivec2 point) const;
		virtual glm::ivec2 GetGlobalPosition() const;
		virtual glm::ivec2 GetPos() const { return m_pos; }
		virtual glm::ivec2 GetSize() const { return m_size; }

		virtual bool MouseLDown(glm::ivec2 point);
		virtual bool MouseRDown(glm::ivec2 point);

		virtual bool MouseLUp(glm::ivec2 point);
		virtual bool MouseRUp(glm::ivec2 point);

		virtual bool MouseLClick(glm::ivec2 point);
		virtual bool MouseRClick(glm::ivec2 point);

		virtual bool MouseMove(glm::ivec2 distance);

		virtual void Render(graphics::GUIRenderer* renderer);
	};

} }