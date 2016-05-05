#include "Texture.h"
#include <soil/SOIL.h>
#include "../Utility.h"

namespace garm { namespace graphics {

	Texture::Texture(std::string path){
		GLubyte* image = SOIL_load_image(path.c_str(), &m_size.x, &m_size.y, &m_channels, SOIL_LOAD_AUTO);
		switch (m_channels) {
		case SOIL_LOAD_L:		m_type = GL_RED;	m_internalFormat = GL_RED; break;
		case SOIL_LOAD_LA:		m_type = GL_RG;		m_internalFormat = GL_RG; break;
		case SOIL_LOAD_RGB:		m_type = GL_RGB;	m_internalFormat = GL_RGB; break;
		case SOIL_LOAD_RGBA:	m_type = GL_RGBA;	m_internalFormat = GL_RGBA; break;
		}
		LoadTexture(image);
	}

	bool Texture::LoadTexture(GLubyte * image){
		CheckGLError();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// Assign texture to ID
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_size.x, m_size.y, 0, m_type, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
		CheckGLError();
		return true;
	}

	void Texture::Bind(int slot){
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

} }