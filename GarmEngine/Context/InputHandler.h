#pragma once

#include "../Math.h"
#include "../Graphics/GUI/Event.h"
#include "Context.h"
#include <functional>

#define NUM_KEYS 255

#define CLICK_TIME 1.0f/5

namespace garm {

	class InputHandler;

	class InputListener {

	public:
		typedef InputHandler notifier_type;

		virtual bool MouseLDown(InputHandler* src, glm::ivec2 point) { return true; }
		virtual bool MouseRDown(InputHandler* src, glm::ivec2 point) { return true; }

		virtual bool MouseLUp(InputHandler* src, glm::ivec2 point) { return true; }
		virtual bool MouseRUp(InputHandler* src, glm::ivec2 point) { return true; }

		virtual bool MouseLClick(InputHandler* src, glm::ivec2 point) { return true; }
		virtual bool MouseRClick(InputHandler* src, glm::ivec2 point) { return true; }
		
		virtual bool MouseMove(InputHandler* src, glm::ivec2 distance) { return true; }
	};

	class InputHandler : public event::Notifier<InputListener> {
		InputHandler(){}
		InputHandler(const InputHandler&);
		InputHandler& operator=(const InputHandler&);
		static InputHandler* m_instance;
	private:
		struct Key {
			bool isDown = false;
			
		} m_keys[NUM_KEYS];

		struct Mouse {
			struct MouseButton{
				bool isDown = false;
				float lastDown = 0;
				float lastUp = 0;
			} m_lmb, m_rmb;

			glm::ivec2 mousePos;
			glm::ivec2 lastMouseMove;

			void MoveMouse(glm::ivec2 pos) {
				lastMouseMove = mousePos - pos;
				mousePos = pos;
			}

			void LMB(bool down);
			void RMB(bool down);

			bool IsLMBDown() { return m_lmb.isDown; }
			bool IsRMBDown() { return m_rmb.isDown; }
		} m_mouse;

	public:
		static InputHandler* GetInstance() {
			if (m_instance == nullptr) m_instance = new InputHandler;
			return m_instance;
		}
		inline glm::ivec2 GetMousePos() { return m_mouse.mousePos; }
		inline bool IsKeyDown(short key) { return m_keys[key].isDown; }
		bool TakeInUnicode(const std::function<void(unsigned)>& func, void* who);
		bool StopTakingUnicode(void* who);

	private:
		std::function<void(unsigned)> m_UnicodeCallback;
		bool m_overrideWithUnicode = false;
		void* m_whoOverridesUnicode = nullptr;
		friend class Context;
		inline void KeyDown(short key) { m_keys[key].isDown = true;	}
		inline void KeyUp(short key) { m_keys[key].isDown = false; }
		inline void UnicodeIn(unsigned c) {	if (m_overrideWithUnicode) m_UnicodeCallback(c); }
		void MouseMove(glm::ivec2 pos);
		void LMB(bool down);
		void RMB(bool down);
	};

#define InputHandler_M garm::InputHandler::GetInstance()

}