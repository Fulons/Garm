#include "Mesh2D.h"
#include "VertexArray.h"
namespace garm { namespace graphics {

	Mesh2D::Mesh2D(Vertex2D * verts, unsigned int numVerts, IndexBuffer* ib, bool generateVA) 
	: m_verts(verts), m_numVerts(numVerts), m_ib(ib) {
		if (generateVA) SetupVertexArray();
	}

	Mesh2D::Mesh2D(VertexArray * va)
	: m_va(va){	}

	Mesh2D::Mesh2D(VertexBuffer * vb, IndexBuffer * ib)	{
		m_va = new VertexArray(vb, ib);
	}

	void Mesh2D::SetupVertexArray() {
		VertexBuffer* vb = new VertexBuffer(GL_STATIC_DRAW);
		BufferAttribLayout layout;
		layout.Push<glm::vec3>("POSITION");
		layout.Push<glm::vec4>("COLOR");
		layout.Push<glm::vec2>("UV");
		vb->SetData(sizeof(Vertex2D) * m_numVerts, m_verts, layout);
		m_va = new VertexArray(vb, m_ib);
	}

	void Mesh2D::Render(){
		if (!m_va) {
			SetupVertexArray();
		}
		m_va->Draw();
	}

} }