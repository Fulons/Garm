#include "TextInputField.h"
#include "../FontRenderable.h"

namespace garm { namespace gui{

	TextInputField::TextInputField(Widget * parent, glm::ivec2 pos, glm::ivec2 size)
	: TextField(parent, pos, size){
		
	}

	bool TextInputField::MouseLClick(glm::ivec2 point){
		if (InputHandler_M->TakeInUnicode([this](unsigned c) { this->UnicodeIn(c); }, this))
			m_takingInUnicode = true;
		return true;
	}

	void TextInputField::UnicodeIn(unsigned c){
		//the first 32 values in the ascii table is not for printing...
		if (c < 32) {
			switch (c) {
			case 8:	//backspace
				if (m_string.size() > 0) {
					m_string.pop_back();
					m_fontRenderable->PopBack();
				}
				break;
			case 27: //escape
				if(m_takingInUnicode)
					InputHandler_M->StopTakingUnicode(this);
				break;
			case 13: //carriage return
				if(m_takingInUnicode)
					InputHandler_M->StopTakingUnicode(this);
				break;
			case 22: { //paste
				std::string pasteStr;
				pasteStr = Context::GetContext()->GetClipboardText();
				if (pasteStr.size() > 0) {
					m_string += pasteStr;
					m_fontRenderable->PushBack(pasteStr);
				}
			}
					 break;
			case 3: //copy
				break;
			}
		}
		else {
			m_string.push_back(c);
			m_fontRenderable->PushBack(std::string(1, c));			
		}
	}

	bool TextInputField::MinimizedToHeader(Widget * src){
		if(m_takingInUnicode)
			InputHandler_M->StopTakingUnicode(this);
		return false;
	}

} }