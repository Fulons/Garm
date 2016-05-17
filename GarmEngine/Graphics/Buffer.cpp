#include "Buffer.h"
#include <assert.h>

namespace garm{ namespace graphics{

	Buffer::Buffer(GLuint bufferID)
	: m_bufferID(bufferID) {}

	Buffer::Buffer(){
		glGenBuffers(1, &m_bufferID);
	}

	Buffer::Buffer(GLsizeiptr size, GLenum usage, const GLvoid * data, GLenum target)
	: m_target(target){
		glGenBuffers(1, &m_bufferID);
		BufferData(size, usage, data);
	}

	Buffer::~Buffer(){
		glDeleteBuffers(1, &m_bufferID);
	}

	void Buffer::BufferData(GLsizeiptr size, GLenum usage, const GLvoid * data){
		Bind();
		m_size = size;
		glBufferData(m_target, size, data, usage);
	}

	void Buffer::EditData(GLintptr offset, GLsizeiptr size, const GLvoid * data){
		Bind();
		glBufferSubData(m_target, offset, size, data);
	}

	void Buffer::MakeBuffers(GLsizei numBuffers, std::vector<Buffer>& buffers){		
		buffers.clear();
		buffers.reserve(numBuffers);
		GLuint* bufferIDs = new GLuint[numBuffers];
		glGenBuffers(numBuffers, bufferIDs);
		for (GLsizei i = 0; i < numBuffers; i++)
			buffers.push_back(Buffer(bufferIDs[i]));
		delete[] bufferIDs;
	}

	void Buffer::Bind(GLenum target){
		if(target == -1)
			glBindBuffer(m_target, m_bufferID);
		else glBindBuffer(target, m_bufferID);
	}

	void* Buffer::MapBufferWrite()
	{
		Bind();
		return glMapBuffer(m_target, GL_WRITE_ONLY);
	}

	void Buffer::UnmapBuffer(){
		Bind();
		glUnmapBuffer(m_target);
	}


} }