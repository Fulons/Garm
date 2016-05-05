#pragma once
#include <gl/glew.h>
#include <string>
#include "../Math.h"


namespace garm { namespace graphics {

	class Texture {
		GLuint m_textureID = 0;
		glm::ivec2 m_size;
		int m_channels;
		GLint m_internalFormat;
		GLint m_type;
	public:
		Texture(std::string path);
		glm::ivec2 GetSize() { return m_size; }
		bool LoadTexture(GLubyte* image);
		void Bind(int slot);
	};

} }