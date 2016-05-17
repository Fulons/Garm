#include "Texture.h"
#include "../Utility.h"
#include <soil/SOIL.h>

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

	Texture::Texture(GLubyte * image, glm::ivec2 size, short channels)
	: m_size(size), m_channels(channels){
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
		CheckGLError();
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

	GLubyte * Texture::LoadDataFromFile(const std::string & path)
	{
		return SOIL_load_image(path.c_str(), &m_size.x, &m_size.y, &m_channels, SOIL_LOAD_AUTO);
	}

	void Texture::EditTexture(glm::ivec2 pos, GLubyte * image, glm::ivec2 size){
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, pos.x, pos.y, size.x, size.y, m_type, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind(int slot){
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glActiveTexture(GL_TEXTURE0 + slot);		
	}

} }