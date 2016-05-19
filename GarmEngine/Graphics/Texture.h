#pragma once
#include "../Math.h"
#include "../Utility.h"
#include <string>
#include <vector>

namespace garm { namespace graphics {

	class TextureOld {
	protected:
		GLuint m_textureID = 0;
		glm::ivec2 m_size;
		int m_channels;
		GLint m_internalFormat;
		GLint m_type;
		TextureOld() {}
		bool LoadTexture(GLubyte* image);
		GLubyte* LoadDataFromFile(const std::string& path);
	public:
		TextureOld(std::string path);
		TextureOld(GLubyte* image, glm::ivec2 size, short channels);
		virtual ~TextureOld() {}	//delete texture
		glm::ivec2 GetSize() { return m_size; }
		void EditTexture(glm::ivec2 pos, GLubyte* image, glm::ivec2 size);
		void Bind(int slot);
		void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
	};

	class Texture {
	protected:
		GLuint m_textureID = -1;
		glm::ivec2 m_size;
		int m_depth;
		GLint m_channels;
		GLint m_format;
		const GLint m_target;

		//virtual void GenTexture();
		//virtual void LoadTexture();
	public:
		Texture(GLint target) : m_target(target) {}
		Texture(GLint target, glm::ivec2 size, GLint format, GLint channels, int depth = 0);
		virtual ~Texture() {}
		void Bind() const;
		void Bind(int slot) const;
		void Unbind() const;
		void SetTextureParameter(GLenum name, GLint param);
		glm::ivec2 GetSize() { return m_size; }
	protected:
		virtual void GenTexture();
	};

	class Texture2D : public Texture {

	protected:
		Texture2D(GLint target) : Texture(target) {}
	public:
		Texture2D(std::string path);
		Texture2D(GLubyte* image, glm::ivec2 size, GLint format, GLint channels = 4);
		virtual ~Texture2D() {}
		//virtual void BufferData(GLubyte* image, glm::ivec2 size, GLint format, GLint channels = 4);
		virtual void BufferSubData(GLubyte* image, glm::ivec2 pos, glm::ivec2 size);
	protected:
		virtual void BufferData(GLubyte* image);
	};

	class Texture3D : public Texture {
	protected:
		Texture3D(GLint target) : Texture(target){}
		Texture3D(GLint target, glm::ivec3 size, GLint format, GLint channels = 4);
		virtual void Init();
	public:
		Texture3D(glm::ivec3 size, GLint format, GLint channels = 4);
		virtual ~Texture3D() {}
		virtual void BufferSubData(GLubyte* image, glm::ivec3 pos, glm::ivec3 size);
		virtual void BufferData(const std::vector<GLubyte*>& images);
	protected:
	};

	class Texture2DArray : public Texture3D {
	public:
		Texture2DArray(glm::ivec3 size, GLint format, GLint channels = 4)
		: Texture3D(GL_TEXTURE_2D_ARRAY, size, format, channels) {};
	};

} }