#pragma once
#include "TextField.h"

namespace garm { namespace gui{	

	class TextInputField : public TextField {
		bool m_takingInUnicode = false;
	public:
		TextInputField(Widget* parent, glm::ivec2 pos, glm::ivec2 size);
		virtual bool MouseLClick(glm::ivec2 point) override;
		void UnicodeIn(unsigned c);
		virtual bool MinimizedToHeader(Widget* src) override;
	};

} }