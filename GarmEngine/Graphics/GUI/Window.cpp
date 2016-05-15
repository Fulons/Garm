#include "Window.h"
#include "Button.h"
#include "../Renderable.h"
#include "../FontRenderable.h"

using garm::graphics::Group;
using garm::graphics::FontRenderable;

namespace garm { namespace gui {

	Window::Window(std::string name, glm::ivec2 pos, glm::ivec2 size, unsigned flags)
	: Widget(nullptr), m_name(name), m_flags(flags){
		SetPosition(pos);
		SetSize(size);
		//Button b(this);
		//b.m_callback = [this]() { this->Close(); };
	}

	void Window::Init(){
		if (IS_FLAG_SET(GUI_WINDOW_HEADER, m_flags)) {
			Button* closeButton = new Button(this);
			closeButton->SetCallback([this]() { this->Close(); });
			AddChild(closeButton);

			Button* ToggleHeaderOnlyButton = new Button(this);
			ToggleHeaderOnlyButton->SetCallback([this]() { this->ToggleHeaderOnly(); });
			AddChild(ToggleHeaderOnlyButton);
		}

		m_RenderableGroup = new Group;
		FontRenderable* fr = new FontRenderable(m_name, { glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) });
		fr->UpdateModelMatrix(glm::translate(glm::mat4(1), glm::vec3(m_size.x + 2, m_size.y + 2 - GUI_WINDOW_HEADER_HEIGHT, 0.0f)));
		m_RenderableGroup->AddChild(fr);
	}

	void Window::Close(){

	}

	void Window::ToggleHeaderOnly(){

	}

	void Window::Render(){

	}

} }