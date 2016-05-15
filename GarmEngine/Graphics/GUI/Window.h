#pragma once
#include "Widget.h"

#define GUI_WINDOW_HEADER_HEIGHT 10
#define IS_FLAG_SET(flag, flags) ((flag & flags) == flag)



namespace garm {
	namespace graphics { class Group; }
	namespace gui {

	enum WindowFlags {
		GUI_WINDOW_RESIZEABLE	= 0x00000001,
		GUI_WINDOW_HEADER		= 0x00000002,
	};



	class Window : public Widget {
	protected:
		std::string m_name;
		bool m_headerOnly = false;
		unsigned m_flags;
		graphics::Group* m_RenderableGroup = nullptr;

		void Init();
		void Close();
	public:
		Window(std::string name, glm::ivec2 pos, glm::ivec2 size, unsigned flags);
		void ToggleHeaderOnly();
		virtual void Render() override;
	};

} }