#pragma once
#include <vector>
#include "../Math.h"
#include <gl/glew.h>

namespace garm { namespace graphics {

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 UV;
	};

	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class Mesh2D {
		Vertex* m_verts = nullptr;
		unsigned int m_numVerts = 0;
		IndexBuffer* m_ib = nullptr;

		VertexArray* m_va = nullptr;
	public:
		Mesh2D(Vertex* verts, unsigned int numVerts, IndexBuffer* ib = nullptr, bool generateVA = false);
		Mesh2D(VertexArray* va);
		Mesh2D(VertexBuffer* vb, IndexBuffer* ib = nullptr);
		~Mesh2D();
		void SetupVertexArray();
		//render and if necessary create the vertexarray
		void Render();
	};

	//class MeshData {
	//	std::vector<glm::vec3> m_positions;
	//	//std::vector<glm::vec3> m_normals;
	//	std::vector<glm::vec4> m_colors;
	//	std::vector<glm::vec2> m_texcords;
	//
	//	std::vector<Vertex> m_vertices;
	//
	//public:
	//	MeshData();
	//	MeshData(std::vector<Vertex>* vertices);
	//};
	//
	//class MeshBuffer {
	//	GLuint m_vbo;
	//public:
	//	MeshBuffer(MeshData* meshData);
	//};

} }