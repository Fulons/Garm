#include "Shader.h"
#include "..\Utility.h"
#include <iostream>
#include <glm\gtc\type_ptr.hpp>

namespace garm {namespace graphics {

	Shader* Shader::shaderInUse = nullptr;

	Shader::Shader(const char* vsPath, const char* fsPath)
		: m_vsPath(vsPath), m_fsPath(fsPath){
		Init();
	}


	Shader::~Shader(){
		glUseProgram(0);
		glDeleteProgram(m_programID);
	}

	void Shader::Use() {
		if (shaderInUse == this) return;
		shaderInUse = this;
		glUseProgram(m_programID);
	}

	GLuint Shader::GetUniformLocation(const char* name){
		auto loc = uniformMap.find(name);
		if (loc != uniformMap.end()) return loc->second;

		GLuint location = glGetUniformLocation(m_programID, name);
		if (location != -1) uniformMap[name] = location;
		else OutErrorMsg((std::string("Uniform Location not found for: ") + name).c_str());
		return location;
	}

	void Shader::SetUniform(const char * name, glm::vec2 val){
		glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, glm::ivec2 val){
		glUniform2iv(GetUniformLocation(name), 1, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, glm::vec3 val){
		glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, glm::ivec3 val){
		glUniform3iv(GetUniformLocation(name), 1, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, glm::vec4 val){
		glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, glm::ivec4 val){
		glUniform4iv(GetUniformLocation(name), 1, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, glm::mat4 val){
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
	}

	void Shader::SetUniform(const char * name, int val){
		glUniform1i(GetUniformLocation(name), val);
	}

	void Shader::SetUniform(const char * name, float val){
		glUniform1f(GetUniformLocation(name), val);
	}

	void Shader::Init(){
		bool good = false;
		std::string vs = ReadFile(m_vsPath.c_str(), &good);
		if (!good) std::cout << "Could not read vertex shader: " << m_vsPath << std::endl;
		std::string fs = ReadFile(m_fsPath.c_str(), &good);
		if (!good) std::cout << "Could not read fragment shader: " << m_fsPath << std::endl;

		GLint success;

		const GLchar* vsFile = vs.c_str();
		GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vsID, 1, &vsFile, nullptr);
		glCompileShader(vsID);
		glGetShaderiv(vsID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			glGetShaderInfoLog(vsID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILES\n" << infoLog << std::endl;
			glDeleteShader(vsID);
			return;
		}

		const GLchar* fsFile = fs.c_str();
		GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fsID, 1, &fsFile, nullptr);
		glCompileShader(fsID);
		glGetShaderiv(fsID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			glGetShaderInfoLog(fsID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILES\n" << infoLog << std::endl;
			glDeleteShader(vsID);
			glDeleteShader(fsID);
			return;
		}

		m_programID = glCreateProgram();
		glAttachShader(m_programID, fsID);
		glAttachShader(m_programID, vsID);
		glLinkProgram(m_programID);
		glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			glDetachShader(m_programID, fsID);
			glDetachShader(m_programID, vsID);
			glDeleteShader(vsID);
			glDeleteShader(fsID);
			glDeleteProgram(m_programID);
			m_programID = 0;
			return;
		}
		glDeleteShader(vsID);
		glDeleteShader(fsID);
	}

} }