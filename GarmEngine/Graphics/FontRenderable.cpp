#include "FontRenderable.h"
#include "MeshData.h"
#include "FontMap.h"
namespace garm{ namespace graphics{

	FontRenderable::FontRenderable(){
		m_buffer = new Buffer;
	}
	
	FontRenderable::FontRenderable(const std::string & str, short fontSize, const std::vector<glm::vec4>& charColors)
		: m_string(str), m_charColors(charColors), m_fontSize(fontSize){
		MakeBuffer();
	}
	
	FontRenderable::~FontRenderable(){
		if (m_buffer) delete m_buffer;
	}
	
	void FontRenderable::MakeBuffer(){
		MeshData mesh;
		std::vector<Vertex>& verts = mesh.GetVertexRef();
		verts.reserve(m_string.length() * 4);
		FontMap* fontMap = FontManager_M->GetFontMap(FONT_SCP_R, m_fontSize);
		unsigned advance = 0;
		std::vector<GLushort>& indices = mesh.GetIndexRef();
		indices.reserve(m_string.length() * 6);
		glm::vec2 textureSize = fontMap->GetSize();
		if (m_charColors.size() == 1) {
			for (unsigned i = 0; i < m_string.length(); i++) {
				Character c = fontMap->GetCharacter(m_string[i]);
				verts.emplace_back(glm::vec3(advance, 0.0f, 0.0f), m_charColors[0], glm::vec2(c.pos.x / textureSize.x, (c.pos.y + c.size.y) / textureSize.y));
				verts.emplace_back(glm::vec3(advance + c.size.x, 0.0f, 0.0f), m_charColors[0], glm::vec2((c.pos.x + c.size.x) / textureSize.x, (c.pos.y + c.size.y) / textureSize.y));
				verts.emplace_back(glm::vec3(advance + c.size.x, c.size.y, 0.0f), m_charColors[0], glm::vec2((c.pos.x + c.size.x) / textureSize.x , c.pos.y / textureSize.y));
				verts.emplace_back(glm::vec3(advance, c.size.y, 0.0f), m_charColors[0], glm::vec2(c.pos.x / textureSize.x, c.pos.y / textureSize.y));
				advance += c.advance >> 6;
				indices.insert(indices.end(), {
					(GLushort)(0 + i * 4), (GLushort)(1 + i * 4), (GLushort)(2 + i * 4),
					(GLushort)(0 + i * 4), (GLushort)(2 + i * 4), (GLushort)(3 + i * 4)
				});
			}	
		}

		m_indexBuffer = mesh.MakeIndexBuffer();
		m_buffer = mesh.MakeBuffer();
		m_texture = fontMap;
	}
	
	void FontRenderable::Render(Shader * shader){
		m_texture->Bind(0);
		m_buffer->Bind();
		m_indexBuffer->Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)sizeof(glm::vec3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
		glDrawElements(GL_TRIANGLES, m_string.size() * 6, GL_UNSIGNED_SHORT, nullptr);
	}

} }