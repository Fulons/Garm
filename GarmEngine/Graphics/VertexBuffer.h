#pragma once
#include "..\Utility.h"
#include <string>
#include <vector>
#include "../Math.h"

namespace garm { namespace graphics {

	struct Attribute {
		std::string name;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLvoid* offset;
	};

	class BufferAttribLayout {
	private:
		std::vector<Attribute> m_layout;
		GLint m_offset = 0;
	public:
		const std::vector<Attribute>& GetLayout() const { return m_layout; }
		GLint GetOffset() const { return m_offset; }
		template<typename T>
		void Push(const std::string& name, GLboolean normalized = false) {
			assert(false);
		}
		
		template<>
		void Push<GLshort>(const std::string& name, GLboolean normalized) {
			Push(sizeof(GLshort), name, 1, GL_SHORT, normalized);
		}

		template<>
		void Push<GLushort>(const std::string& name, GLboolean normalized) {
			Push(sizeof(GLushort), name, 1, GL_UNSIGNED_SHORT, normalized);
		}

		template<>
		void Push<GLint>(const std::string& name, GLboolean normalized) {
			Push(sizeof(GLint), name, 1, GL_INT, normalized);
		}

		template<>
		void Push<GLuint>(const std::string& name,GLboolean normalized) {
			Push(sizeof(GLuint), name, 1, GL_UNSIGNED_INT, normalized);
		}

		template<>
		void Push<glm::ivec2>(const std::string& name, GLboolean normalized) {
			Push(sizeof(glm::ivec2), name, 2, GL_INT, normalized);
		}

		template<>
		void Push<glm::ivec3>(const std::string& name, GLboolean normalized) {
			Push(sizeof(glm::ivec3), name, 3, GL_INT, normalized);
		}

		template<>
		void Push<glm::ivec4>(const std::string& name, GLboolean normalized) {
			Push(sizeof(glm::ivec4), name, 4, GL_INT, normalized);
		}

		template<>
		void Push<GLfloat>(const std::string& name, GLboolean normalized) {
			Push(sizeof(GLfloat), name, 1, GL_FLOAT, normalized);
		}

		template<>
		void Push<glm::vec2>(const std::string& name, GLboolean normalized) {
			Push(sizeof(glm::vec2), name, 2, GL_FLOAT, normalized);
		}

		template<>
		void Push<glm::vec3>(const std::string& name, GLboolean normalized) {
			Push(sizeof(glm::vec3), name, 3, GL_FLOAT, normalized);
		}

		template<>
		void Push<glm::vec4>(const std::string& name, GLboolean normalized) {
			Push(sizeof(glm::vec4), name, 4, GL_FLOAT, normalized);
		}

	private:
		void Push(unsigned int typeSize, const std::string& name, GLint size, GLenum type, GLboolean normalized) {
			m_layout.push_back( { name, size, type, normalized, (GLvoid*)m_offset } );
			m_offset += typeSize;
		}
	};

	class VertexBuffer {
		GLuint m_bufferID;
		GLenum m_usage;
		GLsizeiptr m_size;
		BufferAttribLayout m_layout;
		GLsizei m_vertexCount;
	public:
		VertexBuffer(GLenum usage);
		~VertexBuffer();
		GLsizei GetVertexCount() { return m_vertexCount; }
		void SetupAttribLayout();
		void SetData(GLsizeiptr size, void* data, const BufferAttribLayout& layout);
		void Bind();
		void Unbind();
	};

} }