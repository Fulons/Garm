#pragma once
#include "Widget.h"

#include <functional>

namespace garm { namespace gui {

	class Button : public Widget {
	protected:
		void Init();
		std::function<void()> m_callback;
	public:
		Button(const Widget* parent) : Widget(parent){}
		void SetCallback(const std::function<void()> &callBack) { m_callback = callBack; }
	};

} }