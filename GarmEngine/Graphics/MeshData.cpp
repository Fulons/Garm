#include "MeshData.h"
#include "Buffer.h"

namespace garm { namespace graphics {

	MeshData::MeshData(){
		
	}

	MeshData::MeshData(const std::vector<Vertex>& vertices)
	: m_vertices(vertices){

	}

	MeshData::~MeshData(){
		if (m_posTex != nullptr) delete[] m_posTex;
	}

	void MeshData::AddPositionData(const std::vector<glm::vec3>& positions){
		m_positions.insert(m_positions.end(), positions.begin(), positions.end());
	}

	void MeshData::AddColorData(const std::vector<glm::vec4>& colors){
		m_colors.insert(m_colors.end(), colors.begin(), colors.end());
	}

	void MeshData::AddTexCoordsData(const std::vector<glm::vec2>& texCoords){
		m_texcoords.insert(m_texcoords.end(), texCoords.begin(), texCoords.end());
	}

	void MeshData::AddData(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors, const std::vector<glm::vec2>& texCoords){
		AddPositionData(positions);
		AddColorData(colors);
		AddTexCoordsData(texCoords);
	}

	void MeshData::AddVertexData(const std::vector<Vertex>& vertices){
		m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
	}

	bool MeshData::MakeDataVertexData()
	{
		if (m_positions.size() == m_colors.size() && m_positions.size() == m_texcoords.size()) {
			m_indices.reserve(m_positions.size());
			for (unsigned i = 0; i < m_positions.size(); i++)
				m_vertices.emplace_back(m_positions[i], m_colors[i], m_texcoords[i]);
			m_positions.clear();
			m_colors.clear();
			m_texcoords.clear();
			return true;
		}
		else return false;
	}

	void* MeshData::GetInterLeavedData(){
		if (m_vertices.size() > 0)
			return m_vertices.data();

		if (MakeDataVertexData()) return m_vertices.data();

		if (m_colors.size() == 1) {
			if (m_texcoords.size() == m_positions.size()) {
				m_posTex = new VertexPositionTexCoords[m_positions.size()];
				for (unsigned i = 0; i < m_positions.size(); i++)
					m_posTex[i] = { m_positions[i], m_texcoords[i] };
				return m_posTex;
			}
		}

		return nullptr;
	}

	GLsizeiptr MeshData::GetSize(){
		return sizeof(Vertex) * m_vertices.size();
	}

	Buffer* MeshData::MakeBuffer(GLenum usage){
		Buffer* ret = new Buffer;
		ret->BufferData(GetSize(), usage, GetInterLeavedData());
		return ret;
	}

	Buffer* MeshData::MakeIndexBuffer(GLenum usage)
	{
		if (m_indices.size() < 2) return nullptr;
		Buffer* ret = new Buffer(sizeof(GLushort) * m_indices.size(),
			GL_STATIC_DRAW, m_indices.data(), GL_ELEMENT_ARRAY_BUFFER);
		return ret;
	}



} }