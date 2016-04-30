#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//Opengl inccludes
#include <gl\glew.h>

#include <gl\wglew.h>

#include <gl\GL.h>
#include <gl\glext.h>
#include <gl\wglext.h>
#include <string>

//Link to libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")


#define CheckGLError() _check_gl_error(__FILE__, __LINE__)


bool OutErrorMsg(const char* message);
void _check_gl_error(const char *file, int line);
std::string ReadFile(const char* path, bool* good = nullptr);

