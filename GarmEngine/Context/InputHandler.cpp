#include "InputHandler.h"

namespace garm {

	InputHandler* InputHandler::m_instance = nullptr;

	void InputHandler::Mouse::LMB(bool down) {
		if (m_lmb.isDown == down) return;
		m_lmb.isDown = down;
		if (down) m_lmb.lastDown = Context::GetContext()->GetCurentTime();
		else m_lmb.lastUp = Context::GetContext()->GetCurentTime();
	}

	void InputHandler::Mouse::RMB(bool down) {
		if (m_rmb.isDown == down) return;
		m_rmb.isDown = down;
		if (down) m_rmb.lastDown = Context::GetContext()->GetCurentTime();
		else m_rmb.lastUp = Context::GetContext()->GetCurentTime();
	}

	bool InputHandler::TakeInUnicode(const std::function<void(unsigned)> &func, void * who) {
		if (m_whoOverridesUnicode != nullptr) return false;
		m_UnicodeCallback = func;
		m_overrideWithUnicode = true;
		m_whoOverridesUnicode = who;
		return true;
	}

	bool InputHandler::StopTakingUnicode(void * who) {
		if (m_whoOverridesUnicode == who) {
			m_overrideWithUnicode = false;
			m_whoOverridesUnicode = nullptr;
			return true;
		}
		return false;
	}

	void InputHandler::MouseMove(glm::ivec2 pos){
		m_mouse.MoveMouse(pos);
		Notify(&InputListener::MouseMove, m_mouse.lastMouseMove);
	}

	void InputHandler::LMB(bool down) {
		if (down && !m_mouse.IsLMBDown())
			Notify(&InputListener::MouseLDown, m_mouse.mousePos);
		else if (!down && m_mouse.IsLMBDown()) {
			Notify(&InputListener::MouseLUp, m_mouse.mousePos);
			if (Context::GetContext()->GetCurentTime() - m_mouse.m_lmb.lastDown <= CLICK_TIME)
				Notify(&InputListener::MouseLClick, m_mouse.mousePos);
		}
		m_mouse.LMB(down);
	}

	void garm::InputHandler::RMB(bool down){
		if (down && !m_mouse.IsRMBDown())
			Notify(&InputListener::MouseRDown, m_mouse.mousePos);
		else if (!down && m_mouse.IsRMBDown()) {
			Notify(&InputListener::MouseRUp, m_mouse.mousePos);
			if (Context::GetContext()->GetCurentTime() - m_mouse.m_rmb.lastDown <= CLICK_TIME)
				Notify(&InputListener::MouseRClick, m_mouse.mousePos);
		}
		m_mouse.RMB(down);
	}

}