#pragma once
#include <gl\glew.h>


namespace garm { namespace graphics {

	class IndexBuffer {
		GLuint m_bufferID;
		GLuint m_count;
		GLenum m_type;
	public:
		explicit IndexBuffer(GLuint* data, GLuint count);
		explicit IndexBuffer(GLushort* data, GLuint count);
		~IndexBuffer();

		void Bind();
		void Unbind();
		GLuint GetCount() { return m_count; }
		GLenum GetType() { return m_type; }
	};

} }