#include "Texture.h"
#include "../Utility.h"
#include <soil/SOIL.h>

namespace garm { namespace graphics {

	TextureOld::TextureOld(std::string path){
		GLubyte* image = SOIL_load_image(path.c_str(), &m_size.x, &m_size.y, &m_channels, SOIL_LOAD_AUTO);
		switch (m_channels) {
		case SOIL_LOAD_L:		m_type = GL_RED;	m_internalFormat = GL_RED; break;
		case SOIL_LOAD_LA:		m_type = GL_RG;		m_internalFormat = GL_RG; break;
		case SOIL_LOAD_RGB:		m_type = GL_RGB;	m_internalFormat = GL_RGB; break;
		case SOIL_LOAD_RGBA:	m_type = GL_RGBA;	m_internalFormat = GL_RGBA; break;
		}
		LoadTexture(image);
	}

	TextureOld::TextureOld(GLubyte * image, glm::ivec2 size, short channels)
	: m_size(size), m_channels(channels){
		switch (m_channels) {
		case SOIL_LOAD_L:		m_type = GL_RED;	m_internalFormat = GL_RED; break;
		case SOIL_LOAD_LA:		m_type = GL_RG;		m_internalFormat = GL_RG; break;
		case SOIL_LOAD_RGB:		m_type = GL_RGB;	m_internalFormat = GL_RGB; break;
		case SOIL_LOAD_RGBA:	m_type = GL_RGBA;	m_internalFormat = GL_RGBA; break;
		}
		LoadTexture(image);
	}

	bool TextureOld::LoadTexture(GLubyte * image){
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

	GLubyte * TextureOld::LoadDataFromFile(const std::string & path)
	{
		return SOIL_load_image(path.c_str(), &m_size.x, &m_size.y, &m_channels, SOIL_LOAD_AUTO);
	}

	void TextureOld::EditTexture(glm::ivec2 pos, GLubyte * image, glm::ivec2 size){
		if (size == glm::ivec2(0, 0)) return;
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, pos.x, pos.y, size.x, size.y, m_type, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureOld::Bind(int slot){
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	////////////////////////////////////////////////////////////////////////

	Texture::Texture(GLint target, glm::ivec2 size, GLint format, GLint channels, int depth)
	: m_target(target), m_size(size), m_format(format), m_channels(channels), m_depth(depth){}

	void Texture::Bind() const{
		glBindTexture(m_target, m_textureID);
	}

	void Texture::Bind(int slot) const{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture::Unbind() const{
		glBindTexture(m_target, 0);
	}

	void Texture::SetTextureParameter(GLenum name, GLint param){
		Bind();
		glTexParameteri(m_target, name, param);
	}

	void Texture::GenTexture(){
		glGenTextures(1, &m_textureID);
	}

	Texture2D::Texture2D(std::string path)
	: Texture(GL_TEXTURE_2D){
		GLubyte* image = SOIL_load_image(path.c_str(), &m_size.x, &m_size.y, &m_channels, SOIL_LOAD_AUTO);
		BufferData(image);
	}

	Texture2D::Texture2D(GLubyte * image, glm::ivec2 size, GLint format, GLint channels)
	: Texture(GL_TEXTURE_2D, size, channels, format){
		BufferData(image);
	}

	//void Texture2D::BufferData(GLubyte * image, glm::ivec2 size, GLint format, GLint channels){
	//
	//}

	void Texture2D::BufferSubData(GLubyte * image, glm::ivec2 pos, glm::ivec2 size){
		if (size == glm::ivec2(0, 0)) return;
		Bind();
		glTexSubImage2D(m_target, 0, pos.x, pos.y, size.x, size.y, m_format, GL_UNSIGNED_BYTE, image);
	}

	void Texture2D::BufferData(GLubyte * image){
		if (m_textureID == -1) GenTexture();
		Bind();
		glTexImage2D(m_target, 0, m_format, m_size.x, m_size.y, 0, m_format, GL_UNSIGNED_BYTE, image);
	}


	Texture3D::Texture3D(GLint target, glm::ivec3 size, GLint format, GLint channels)
		: Texture(target, glm::ivec2(size.x, size.y), format, channels, size.z) {
		Init();
	}

	void Texture3D::Init(){
		GenTexture();
		Bind();
		glTexStorage3D(m_target, 0, m_format, m_size.x, m_size.y, m_depth);
	}

	Texture3D::Texture3D(glm::ivec3 size, GLint format, GLint channels)
	: Texture(GL_TEXTURE_3D, glm::ivec2(size.x, size.y), format, channels, size.z){
		Init();
	}

	void Texture3D::BufferSubData(GLubyte * image, glm::ivec3 pos, glm::ivec3 size){
		if (size == glm::ivec3(0, 0, 0)) return;
		Bind();
		glTexSubImage3D(m_target, 0, pos.x, pos.y, pos.z, size.x, size.y, size.z, m_format, GL_UNSIGNED_BYTE, image);
	}

	void Texture3D::BufferData(const std::vector<GLubyte*>& images){
		Bind();
		for (unsigned i = 0; i < images.size(); i++) {
			if(images[i])
				glTexSubImage3D(m_target, 0, 0, 0, i, m_size.x, m_size.y, 1, m_format, GL_UNSIGNED_BYTE, images[i]);
		}
	}

} }