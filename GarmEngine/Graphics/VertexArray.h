#pragma once
#include <gl/glew.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace garm { namespace graphics {

	class VertexArray {

		GLuint m_bufferID;
		VertexBuffer* m_vertexBuffer = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;
	public:
		VertexArray(VertexBuffer* vb, IndexBuffer* ib = nullptr);
		~VertexArray();
		void Bind();
		void Unbind();
		void Draw(bool forceElementDraw = false);
	};
	
} }