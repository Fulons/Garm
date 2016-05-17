#pragma once
#include "../Math.h"
#include <gl/glew.h>
#include <string>


namespace garm { namespace graphics {

	class Texture {
	protected:
		GLuint m_textureID = 0;
		glm::ivec2 m_size;
		int m_channels;
		GLint m_internalFormat;
		GLint m_type;
		Texture(){}
		bool LoadTexture(GLubyte* image);
		GLubyte* LoadDataFromFile(const std::string& path);
	public:
		Texture(std::string path);
		Texture(GLubyte* image, glm::ivec2 size, short channels);
		virtual ~Texture(){}	//delete texture
		glm::ivec2 GetSize() { return m_size; }
		void EditTexture(glm::ivec2 pos, GLubyte* image, glm::ivec2 size);
		void Bind(int slot);
		void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
	};

} }