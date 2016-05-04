#pragma once
#include <glm/glm.hpp>

namespace garm { namespace graphics {

	struct Vertex2D {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 UV;
	};

	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class Mesh2D {
		Vertex2D* m_verts = nullptr;
		unsigned int m_numVerts = 0;
		IndexBuffer* m_ib = nullptr;

		VertexArray* m_va = nullptr;
	public:
		Mesh2D(Vertex2D* verts, unsigned int numVerts, IndexBuffer* ib = nullptr, bool generateVA = false);
		Mesh2D(VertexArray* va);
		Mesh2D(VertexBuffer* vb, IndexBuffer* ib = nullptr);
		~Mesh2D();
		void SetupVertexArray();
		//render and if necessary create the vertexarray
		void Render();
	};

} }