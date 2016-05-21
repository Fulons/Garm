#pragma once
#include "TextField.h"

namespace garm { namespace gui{

	class TextInputField : public TextField {

	public:
		TextInputField(Widget* parent, glm::ivec2 pos, glm::ivec2 size);
		virtual bool MouseLClick(glm::ivec2 point) override;
		void UnicodeIn(unsigned c);
	};

} }