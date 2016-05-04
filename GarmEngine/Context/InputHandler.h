#pragma once

#include "../Math.h"

#define NUM_KEYS 255

namespace garm {

	class InputHandler {

	private:
		struct Key {
			bool isDown = false;
			
		}static m_keys[NUM_KEYS];

		struct Mouse {
			glm::ivec2 mousePos;
			glm::ivec2 lastMouseMove;
			void MoveMouse(glm::ivec2 pos) {
				lastMouseMove = mousePos - pos;
				mousePos = pos; }
		}static m_mouse;

	public:
		inline static glm::ivec2 GetMousePos() { return m_mouse.mousePos; }
		inline static bool IsKeyDown(short key) { return m_keys[key].isDown; }
		
	private:
		friend class Context;
		inline static void KeyDown(short key) { m_keys[key].isDown = true; }
		inline static void KeyUp(short key) { m_keys[key].isDown = false; }
		inline static void MouseMove(glm::ivec2 pos) { m_mouse.MoveMouse(pos); }
	};

}