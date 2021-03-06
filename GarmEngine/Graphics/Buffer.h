#pragma once
#include <gl/glew.h>
#include <vector>

namespace garm{ namespace graphics{

	class Buffer {
	protected:
		GLenum m_target = GL_ARRAY_BUFFER;
		GLuint m_bufferID;
		GLsizeiptr m_size;
		Buffer(GLuint bufferID);
	public:
		Buffer();
		Buffer(GLsizeiptr size, GLenum usage = GL_STATIC_DRAW, const GLvoid* data = nullptr, GLenum target = GL_ARRAY_BUFFER);
		virtual ~Buffer();
		virtual void BufferData(GLsizeiptr size, GLenum usage = GL_STATIC_DRAW, const GLvoid* data = nullptr);
		virtual void EditData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
		static void MakeBuffers(GLsizei numBuffers, std::vector<Buffer>& buffers);
		virtual void Bind(GLenum target = -1);
		virtual void* MapBufferWrite();
		virtual void UnmapBuffer();
		GLsizeiptr GetSize() { return m_size; }
		template <typename var>
		unsigned GetVarCount() { return m_size / sizeof(var); }
		void SetTarget(GLenum target) { m_target = target; }
	};

} }