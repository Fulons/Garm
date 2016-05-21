#include "Context.h"
#include "InputHandler.h"
//For console
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>


namespace {
	garm::Context* g_Context = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_Context) return g_Context->MsgProc(hWnd, msg, wParam, lParam);
	else return DefWindowProc(hWnd, msg, wParam, lParam);
}

namespace garm {

	Context* Context::m_currentContext = nullptr;

	Context::Context(HINSTANCE hInstance)
		: m_hAppInstance(hInstance)
	{
		m_clientWidth = 800;
		m_clientHeight = 600;
		m_appTitle = "OPENGL APP";
		m_windowStyle = WS_OVERLAPPED | WS_SIZEBOX | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;	//WS_POPUP
		g_Context = this;
		m_currentContext = this;
	}

	int Context::Run(){

		//Calculate TIMING
		__int64 prevTime{ 0 };
		QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
		__int64 countsPerSec{ 0 };
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		float secondsPerCount = 1.0f / countsPerSec;
		MSG msg = {};
		while (WM_QUIT != msg.message) {
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				//Calculate DT
				__int64 curTime = 0;
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
				float deltaTime = (curTime - prevTime) * secondsPerCount;
				m_currentTime = curTime * secondsPerCount;
				//Update
				Update(deltaTime);
				Render();
				CalculateFPS(deltaTime);
				//glFlush();
				//glFinish();				
				SwapBuffers(m_hDevContext);
				prevTime = curTime;
				m_frameCount++;

			}			
		}
		Shutdown();
		return static_cast<int>(msg.wParam);
	}
	//TODO: make error messages
	std::string Context::GetClipboardText(){
		if (!OpenClipboard(nullptr)) return "";
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr) return "";
		char* txt = static_cast<char*>(GlobalLock(hData));
		if (txt == nullptr) return "";
		std::string ret(txt);
		GlobalUnlock(hData);
		CloseClipboard();
		return ret;
		
	}

	LRESULT Context::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CHAR:
			InputHandler_M->UnicodeIn(wParam);
			return 0;
		case WM_MOUSEMOVE:
			InputHandler_M->MouseMove(glm::ivec2(LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_LBUTTONDOWN:
			InputHandler_M->LMB(true);
			break;
		case WM_RBUTTONDOWN:
			InputHandler_M->RMB(true);
			break;
		case WM_LBUTTONUP:
			InputHandler_M->LMB(false);
			break;
		case WM_RBUTTONUP:
			InputHandler_M->RMB(false);
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) PostQuitMessage(0);
			InputHandler_M->KeyDown(wParam);
			break;
		case WM_KEYUP:
			InputHandler_M->KeyUp(wParam);
			break;
		default:;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	bool Context::Init() {
		if (!InitWindow()) return false;
		if (!InitGL()) return false;

		return true;
	}

	bool Context::InitWindow()
	{
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hInstance = m_hAppInstance;
		wcex.lpfnWndProc = MainWndProc;
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wcex.lpszClassName = "CONTEXTWNDCLASS";
		wcex.lpszMenuName = NULL;	//NO MENU

		

		if (!RegisterClassEx(&wcex)) return OutErrorMsg("Failed to register wnd class");

		//ADjust window rect
		RECT r = { 0, 0, (LONG)m_clientWidth, (LONG)m_clientHeight };
		AdjustWindowRect(&r, m_windowStyle, FALSE);

		int w = r.right - r.left;
		int h = r.bottom - r.top;
		int x = GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2;
		int y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

		//create our window
		m_hAppWnd = CreateWindow("CONTEXTWNDCLASS", m_appTitle, m_windowStyle, x, y, w, h, NULL, NULL, m_hAppInstance, NULL);
		if (!m_hAppWnd) return OutErrorMsg("Failed to create window");

		//show window
		ShowWindow(m_hAppWnd, SW_SHOW);

		//Show Console
#if 0
		AllocConsole();

		HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
		FILE* hf_out = _fdopen(hCrt, "w");
		setvbuf(hf_out, NULL, _IONBF, 1);
		*stdout = *hf_out;

		HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
		hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
		FILE* hf_in = _fdopen(hCrt, "r");
		setvbuf(hf_in, NULL, _IONBF, 128);
		*stdin = *hf_in;
		//std::ios::sync_with_stdio();
#elif 1
		//This seems to simple compared to earlier ways of doing it...
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "r", stdin);
#elif 0
		int hConHandle;
		long lStdHandle;
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		FILE *fp;

		// allocate a console for this app
		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = 500;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		// redirect unbuffered STDOUT to the console
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stdout = *fp;

		setvbuf(stdout, NULL, _IONBF, 0);

		// redirect unbuffered STDIN to the console

		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "r");
		*stdin = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);

		// redirect unbuffered STDERR to the console
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stderr = *fp;

		setvbuf(stderr, NULL, _IONBF, 0);

		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
		// point to console as well
		std::ios::sync_with_stdio();
#elif 0
		int hConHandle;

		long lStdHandle;

		CONSOLE_SCREEN_BUFFER_INFO coninfo;

		FILE *fp;

		// allocate a console for this app

		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

			&coninfo);

		coninfo.dwSize.Y = 500;

		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

			coninfo.dwSize);

		// redirect unbuffered STDOUT to the console

		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stdout = *fp;

		setvbuf(stdout, NULL, _IONBF, 0);

		// redirect unbuffered STDIN to the console

		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "r");

		*stdin = *fp;

		setvbuf(stdin, NULL, _IONBF, 0);

		// redirect unbuffered STDERR to the console

		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stderr = *fp;

		setvbuf(stderr, NULL, _IONBF, 0);

		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog

		// point to console as well

		std::ios::sync_with_stdio();
#endif

		return true;
	}

	bool Context::InitGL()
	{
		m_hDevContext = GetDC(m_hAppWnd);

		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		int format = ChoosePixelFormat(m_hDevContext, &pfd);
		if (!SetPixelFormat(m_hDevContext, format, &pfd))
			return OutErrorMsg("Failed to set pixel format");

		m_hGLRenderContext = wglCreateContext(m_hDevContext);
		if (!wglMakeCurrent(m_hDevContext, m_hGLRenderContext))
			return OutErrorMsg("Failed to create and activate render context");


		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cout << "ERROR::GLEW::INIT: " << glewGetErrorString(err) << std::endl;
			return false;
		}
		//Turning off v-sync
		//wglSwapIntervalEXT(0);

		return true;
	}

	void Context::Shutdown()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hGLRenderContext);
		ReleaseDC(m_hAppWnd, m_hDevContext);
	}

	void Context::CalculateFPS(float dt)
	{
		static float elapsed = 0;
		static int frameCount = 0;
		elapsed += dt;
		frameCount++;
		if (elapsed >= 1.0f) {
			m_FPS = (float)frameCount;
			std::stringstream ss;
			ss << m_appTitle << " FPS: " << m_FPS << " " << glGetString(GL_VENDOR);
			SetWindowText(m_hAppWnd, ss.str().c_str());
			elapsed = 0.0f;
			frameCount = 0;
		}
	}

}