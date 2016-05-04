#pragma once
#include "../Math.h"

#include <GL/glew.h>
#include <string>
#include <map>

namespace garm { namespace graphics {

	class Shader
	{
	public:
		Shader(const char* vsPath, const char* fsPath);
		~Shader();

		std::map<const char*, GLuint> uniformMap;

		void Use();
		void SetUniform(const char* name, glm::vec2 val);
		void SetUniform(const char* name, glm::ivec2 val);
		void SetUniform(const char* name, glm::vec3 val);
		void SetUniform(const char* name, glm::ivec3 val);
		void SetUniform(const char* name, glm::vec4 val);
		void SetUniform(const char* name, glm::ivec4 val);
		void SetUniform(const char* name, glm::mat4 val);
		void SetUniform(const char* name, int val);
		void SetUniform(const char* name, float val);
	private:
		GLuint m_programID;
		std::string m_vsPath, m_fsPath;
		static Shader* shaderInUse;

		GLuint GetUniformLocation(const char* name);
		
	private:		
		void Init();
	};

}}