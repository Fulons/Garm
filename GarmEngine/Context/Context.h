#pragma once
#include "../Utility.h"
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glext.h>
#include <gl/wglext.h>


namespace garm {

	class Context
	{
	public:
		Context(HINSTANCE hInstance);
		virtual ~Context() {}
		virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
		virtual bool Init();
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;

		int Run();

		UINT GetClientWidth() { return m_clientWidth; }
		UINT GetClientHeight() { return m_clientHeight; }
		float GetCurentTime() { return m_currentTime; }

		//might want to limit access to the context like this later on
		//make the getcurtime functions and so on static instead
		static Context* GetContext() { return m_currentContext; }
		std::string GetClipboardText();

	private:
		HWND			m_hAppWnd = nullptr;
		HINSTANCE		m_hAppInstance;
		HDC				m_hDevContext = nullptr;
		HGLRC			m_hGLRenderContext = nullptr;
		UINT			m_clientWidth;
		UINT			m_clientHeight;
		DWORD			m_windowStyle;
		char*			m_appTitle;
		float			m_FPS;
		unsigned int	m_frameCount = 0;
		float			m_currentTime;

		bool InitWindow();
		bool InitGL();
		void Shutdown();
		void CalculateFPS(float dt);

		static Context* m_currentContext;
	};

}