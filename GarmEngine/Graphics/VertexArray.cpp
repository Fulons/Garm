#include "VertexArray.h"

namespace garm { namespace graphics {

	VertexArray::VertexArray(VertexBuffer* vb, IndexBuffer* ib)
		:	m_vertexBuffer(vb), m_IndexBuffer(ib) {
		glGenVertexArrays(1, &m_bufferID);
		glBindVertexArray(m_bufferID);
		vb->SetupAttribLayout();
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray() {
		m_vertexBuffer->Unbind();
		glDeleteVertexArrays(1, &m_bufferID);
	}

	void VertexArray::Bind(){
		glBindVertexArray(m_bufferID);
		m_vertexBuffer->Bind();
		if (m_IndexBuffer) m_IndexBuffer->Bind();
	}

	void VertexArray::Unbind(){
		glBindVertexArray(0);
	}

	void VertexArray::Draw(bool forceElementDraw){
		Bind();
		if (m_IndexBuffer != nullptr || forceElementDraw) {
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), m_IndexBuffer->GetType(), nullptr);
		}
		else
			glDrawArrays(GL_TRIANGLES, 0, m_vertexBuffer->GetVertexCount());
		Unbind();
	}


} }
