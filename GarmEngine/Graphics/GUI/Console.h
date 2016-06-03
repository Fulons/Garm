#pragma once
#include "Window.h"
#include "TextInputField.h"

namespace garm { namespace gui{


	class TextReciever {
		std::vector<std::string> m_history;
	public:
		std::string* HistoryBack();
		std::string* HistoryForward();
		std::string* HistoryClear();

		virtual void Insert(const std::string& s);
		virtual std::string AutoComplete(const std::string& s);
		virtual const std::vector<std::string>& AutoCompleteList(const std::string& s);
	};

	class Console : public TextReciever {
		Window* m_window;
		ConsoleInputField* m_inputField;
	public:
		Console(const glm::ivec2& pos, const glm::ivec2& size);
	};

	class ConsoleInputField : public TextInputField {
		TextReciever* m_console;
	public:
		ConsoleInputField(Widget* parent, TextReciever* console, glm::ivec2 pos, glm::ivec2 size);
		void MenuCallback(unsigned i);

	};

} }