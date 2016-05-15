#pragma once
#include "../Math.h"
#include <vector>
#include <gl/glew.h>

namespace garm { namespace graphics {

	struct Vertex {
		Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2& UV)
			: position(position), color(color), UV(UV){}
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 UV;
	};

	struct VertexPositionTexCoords {
		glm::vec3 position;
		glm::vec2 UV;
	};

	class Buffer;

	class MeshData {
		std::vector<glm::vec3> m_positions;
		//std::vector<glm::vec3> m_normals;
		std::vector<glm::vec4> m_colors;
		std::vector<glm::vec2> m_texcoords;
	
		std::vector<Vertex> m_vertices;
		std::vector<GLushort> m_indices;
		VertexPositionTexCoords* m_posTex = nullptr;
	public:
		MeshData();
		MeshData(const std::vector<Vertex>& vertices);
		~MeshData();
		void AddPositionData(const std::vector<glm::vec3>& positions);
		void AddColorData(const std::vector<glm::vec4>& colors);
		void AddTexCoordsData(const std::vector<glm::vec2>& texCoords);
		void AddData(const std::vector<glm::vec3>& positions,
			const std::vector<glm::vec4>& colors,
			const std::vector<glm::vec2>& texCoords);
		void AddSprite(const glm::vec3 pos, const glm::vec2 size, const std::vector<glm::vec2>& texCoords, bool genIndices = true);
		void AddSprite(const glm::vec3 pos, const glm::vec2 size, bool genIndices = true);
		void AddVertexData(const std::vector<Vertex>& vertices);
		bool MakeDataVertexData();
		void* GetInterLeavedData();
		std::vector<Vertex>& GetVertexRef() { return m_vertices; }
		std::vector<GLushort>& GetIndexRef() { return m_indices; }
		GLsizeiptr GetSize();
		Buffer* MakeBuffer(GLenum usage = GL_STATIC_DRAW);
		Buffer* MakeIndexBuffer(GLenum usage = GL_STATIC_DRAW);
	};

} }