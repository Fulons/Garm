#include "Utility.h"
#include <fstream>
#include <sstream>
#include <iostream>


bool OutErrorMsg(const char * message)
{
	//MessageBox(NULL, message, NULL, NULL);
	std::cout << message << std::endl;
	return false;
}

std::string ReadFile(const char* path, bool* good)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::string str("Could not find file: ");
		str += path;
		OutErrorMsg(str.c_str());
		if (good) *good = false;
		return std::string();
	}

	std::stringstream ret;
	ret << file.rdbuf();
	file.close();
	if (good) *good = true;
	return ret.str();
}

void _check_gl_error(const char *file, int line) {
	GLenum err(glGetError());

	while (err != GL_NO_ERROR) {
		std::string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		default: error = std::to_string(err).c_str();
		}

		std::cout << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
		err = glGetError();
	}
}
