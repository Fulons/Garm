#include "../Utility.h"
#include "FontRenderable.h"
#include "MeshData.h"
#include "FontMap.h"

namespace garm{ namespace graphics{

	FontRenderable::FontRenderable(){
		//m_buffer = new Buffer;
	}
	
	FontRenderable::FontRenderable(const std::string & str, short fontSize, const std::vector<glm::vec4>& charColors)
		: m_string(str), m_charColors(charColors), m_fontSize(fontSize){
		MakeBuffer();
	}
	
	FontRenderable::~FontRenderable(){
		if (m_buffer) delete m_buffer;
	}
	
	struct FontVertex {
		FontVertex(const glm::vec3& pos, const glm::vec4& color, const glm::vec3& uv)
		: pos(pos), color(color), uv(uv){}
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec3 uv;
	};

	void FontRenderable::MakeBuffer(){
		MeshData mesh;
		std::vector<FontVertex> verts;
		verts.reserve(m_string.length() * 4);

		unsigned advance = 0;
		std::vector<GLushort> indices;
		indices.reserve(m_string.length() * 6);
		glm::vec2 textureSize = FontManager_M->GetTextureSize();
		CheckGLError();
		if (m_charColors.size() == 1) {
			for (unsigned i = 0; i < m_string.length(); i++) {
				Character c = FontManager_M->GetCharacter(m_string[i], m_fontSize);
				CheckGLError();
				verts.emplace_back(glm::vec3(advance + c.bearing.x, c.bearing.y - c.size.y , 0.0f),					m_charColors[0], glm::vec3(c.pos.x / textureSize.x,					(c.pos.y + c.size.y) / textureSize.y,	c.textureID));
				verts.emplace_back(glm::vec3(advance + c.bearing.x + c.size.x, c.bearing.y - c.size.y, 0.0f),		m_charColors[0], glm::vec3((c.pos.x + c.size.x) / textureSize.x,	(c.pos.y + c.size.y) / textureSize.y,	c.textureID));
				verts.emplace_back(glm::vec3(advance + c.bearing.x + c.size.x, c.bearing.y, 0.0f),	m_charColors[0], glm::vec3((c.pos.x + c.size.x) / textureSize.x ,	c.pos.y / textureSize.y,				c.textureID));
				verts.emplace_back(glm::vec3(advance + c.bearing.x, c.bearing.y, 0.0f),				m_charColors[0], glm::vec3(c.pos.x / textureSize.x,					c.pos.y / textureSize.y,				c.textureID));
				advance += c.advance >> 6;
				indices.insert(indices.end(), {
					(GLushort)(0 + i * 4), (GLushort)(1 + i * 4), (GLushort)(2 + i * 4),
					(GLushort)(0 + i * 4), (GLushort)(2 + i * 4), (GLushort)(3 + i * 4)
				});
			}	
		}
		CheckGLError();

		m_buffer = new Buffer(sizeof(FontVertex) * verts.size(), GL_STATIC_DRAW, verts.data());
		m_indexBuffer = new Buffer(sizeof(GLushort) * indices.size(), GL_STATIC_DRAW, indices.data(), GL_ELEMENT_ARRAY_BUFFER);
		m_texture = FontManager_M->GetTexture();
	}
	
	void FontRenderable::Render(Shader * shader){
		shader->SetUniform("t", 0);
		m_texture->Bind(0);
		m_buffer->Bind();
		m_indexBuffer->Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::FontVertex), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::FontVertex), (GLvoid*)sizeof(glm::vec3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::FontVertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
		glDrawElements(GL_TRIANGLES, m_string.size() * 6, GL_UNSIGNED_SHORT, nullptr);
		CheckGLError();
	}

} }