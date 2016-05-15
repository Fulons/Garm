#include "GUILayer.h"
#include "../Shader.h"

using garm::gui::Window;


namespace garm { namespace graphics{

	void GUILayer::AddWindow(Window* window){
		m_windows.push_back(window);
	}

	void GUILayer::OnRender(){

	}

} }