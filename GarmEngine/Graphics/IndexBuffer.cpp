#include "IndexBuffer.h"

namespace garm {namespace graphics {

	IndexBuffer::IndexBuffer(GLuint* data, GLuint count) 
		: m_count(count), m_type(GL_UNSIGNED_INT){
		glGenBuffers(1, &m_bufferID);
		Bind();		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, GL_STATIC_DRAW);
		Unbind();
	}

	IndexBuffer::IndexBuffer(GLushort* data, GLuint count)
		: m_count(count), m_type(GL_UNSIGNED_SHORT)	{
		glGenBuffers(1, &m_bufferID);
		Bind();		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * count, data, GL_STATIC_DRAW);
		Unbind();
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_bufferID);
	}

	void IndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	}

	void IndexBuffer::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} }