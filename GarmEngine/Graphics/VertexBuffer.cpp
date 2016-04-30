#include "VertexBuffer.h"


namespace garm { namespace graphics {

	VertexBuffer::VertexBuffer(GLenum usage) : m_usage(usage) {
		glGenBuffers(1, &m_bufferID);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_bufferID);
	}

	void VertexBuffer::SetupAttribLayout() {
		std::vector<Attribute> layout = m_layout.GetLayout();
		for (GLushort i = 0; i < layout.size(); i++) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, layout[i].size, layout[i].type, layout[i].normalized, m_layout.GetOffset(), layout[i].offset);
		}
	}

	void VertexBuffer::SetData(GLsizeiptr size, void * data, const BufferAttribLayout& layout) {
		m_layout = layout;
		m_vertexCount = size / layout.GetOffset();
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, m_usage);
	}

	void VertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	void VertexBuffer::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}}