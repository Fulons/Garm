#pragma once
#include "Widget.h"
#define GUI_WINDOW_HEADER_HEIGHT 20

#define IS_FLAG_SET(flag, flags) ((flag & flags) == flag)



namespace garm {
	namespace graphics { class Group; }
	namespace gui {

	enum WindowFlags {
		GUI_WINDOW_RESIZEABLE	= 0x00000001,
		GUI_WINDOW_HEADER		= 0x00000002,
	};

	class Window : public Widget{
	protected:
		std::string m_name;
		bool m_headerOnly = false;
		unsigned m_flags;
		graphics::GUISprite m_backgroundSprite;
		Widget* m_header;
	public:
		Window(std::string name, glm::ivec2 pos, glm::ivec2 size, unsigned flags);
		void Close();
		void ToggleHeaderOnly();
		const std::string& GetName() { return m_name; }
		virtual void Render(graphics::GUIRenderer* renderer) override;
		virtual bool ContainsInParentCoordinate(glm::ivec2 point) const override;
		virtual bool ContainsInGlobalCoordinate(glm::ivec2 point) const override;
		virtual bool ContainsInLocalCoordinate(glm::ivec2 point) const override;
	};

	

} }