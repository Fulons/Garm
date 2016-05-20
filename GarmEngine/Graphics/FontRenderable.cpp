#include "../Utility.h"
#include "FontRenderable.h"
#include "MeshData.h"
#include <iostream>

namespace garm{ namespace graphics{

	FontRenderable::FontRenderable(){
		//m_buffer = new Buffer;
	}
	
	FontRenderable::FontRenderable(const std::string & str, short fontSize, const std::vector<glm::vec4>& charColors)
		: m_string(str), m_charColors(charColors), m_fontSize(fontSize){
		m_renderFrom = 0;
		m_renderTo = str.size();
		m_buffer = new Buffer();
		m_indexBuffer = new Buffer();
		m_indexBuffer->SetTarget(GL_ELEMENT_ARRAY_BUFFER);
		MakeBuffer();
	}

	void FontRenderable::SetString(const std::string & str){
		m_newString = str;
		m_newStringSet = true;
	}

	void FontRenderable::SetColor(const std::vector<glm::vec4>& charColors){
		m_charColors = charColors;
		m_colorsSet = true;
	}

	void FontRenderable::SetFontSize(short fontSize){
		m_fontSize = fontSize;
		m_fontSizeSet = true;
	}
	
	void FontRenderable::PushBack(const std::string& str){
		if(str.size() == 1)
			if (m_renderTo < m_string.size()) {
				if (m_string[m_renderTo] == str[0]) {
					++m_renderTo;
					return;
				}
				else {
					m_string[m_renderTo] = str[0];
					UpdateCharBuffer(m_renderTo);	//Calling untested scary function
					++m_renderTo;
					return;
				}
			}
		m_string = m_string.substr(0, m_renderTo);
		AppendToBuffer(str);
		++m_renderTo;
	}

	void FontRenderable::RefreshBuffer(){
		if (m_newStringSet) {
			m_string = m_newString;
			m_newString.clear();
			MakeBuffer();
		}
		if (m_colorsSet || m_fontSizeSet) MakeBuffer();
		m_newStringSet = m_colorsSet = m_fontSizeSet = false;
	}

	void FontRenderable::PopBack(unsigned n) { --m_renderTo; }

	void FontRenderable::PopFront(unsigned n) { --m_renderFrom; }

	FontRenderable::~FontRenderable(){
		if (m_buffer) delete m_buffer;
	}	

	void FontRenderable::MakeBuffer(){
		m_texture = FontManager_M->GetTexture();
		if (m_string.size() == 0) return;
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
				MakeCharVerts(verts, c, advance, textureSize);
				m_advance.push_back(advance);
				advance += c.advance >> 6;
				indices.insert(indices.end(), {
					(GLushort)(0 + i * 4), (GLushort)(1 + i * 4), (GLushort)(2 + i * 4),
					(GLushort)(0 + i * 4), (GLushort)(2 + i * 4), (GLushort)(3 + i * 4)
				});
			}	
		}
		CheckGLError();

		m_buffer->BufferData(sizeof(FontVertex) * verts.size(), GL_STATIC_DRAW, verts.data());
		m_indexBuffer->BufferData(sizeof(GLushort) * indices.size(), GL_STATIC_DRAW, indices.data());
	}

	void FontRenderable::MakeCharVerts(std::vector<FontVertex>& verts, const Character & c, unsigned advance, const glm::vec2& textureSize){
		verts.emplace_back(glm::vec3(advance + c.bearing.x, c.bearing.y - c.size.y , 0.0f),					m_charColors[0], glm::vec3(c.pos.x / textureSize.x,					(c.pos.y + c.size.y) / textureSize.y,	c.textureID));
		verts.emplace_back(glm::vec3(advance + c.bearing.x + c.size.x, c.bearing.y - c.size.y, 0.0f),		m_charColors[0], glm::vec3((c.pos.x + c.size.x) / textureSize.x,	(c.pos.y + c.size.y) / textureSize.y,	c.textureID));
		verts.emplace_back(glm::vec3(advance + c.bearing.x + c.size.x, c.bearing.y, 0.0f),	m_charColors[0], glm::vec3((c.pos.x + c.size.x) / textureSize.x ,	c.pos.y / textureSize.y,				c.textureID));
		verts.emplace_back(glm::vec3(advance + c.bearing.x, c.bearing.y, 0.0f),				m_charColors[0], glm::vec3(c.pos.x / textureSize.x,					c.pos.y / textureSize.y,				c.textureID));
	}

	void FontRenderable::MakeCharIndices(std::vector<GLushort>& indices, unsigned index){
		indices.insert(indices.end(), {
			(GLushort)(0 + index * 4), (GLushort)(1 + index * 4), (GLushort)(2 + index * 4),
			(GLushort)(0 + index * 4), (GLushort)(2 + index * 4), (GLushort)(3 + index * 4)
		});
	}
	

	void FontRenderable::UpdateCharBuffer(unsigned index){
		glm::vec2 textureSize = FontManager_M->GetTextureSize();
		Character c = FontManager_M->GetCharacter(m_string[index], m_fontSize);
		std::vector<FontVertex> verts;
		MakeCharVerts(verts, c, m_advance[index], textureSize);
		if (((c.advance >> 6) == m_advance[index] - m_advance[index - 1]) ||
			(m_string.size() == index + 1)) {
			m_buffer->EditData(index * sizeof(FontVertex) * 4, sizeof(FontVertex) * 4, verts.data());
		}
		else {
			m_advance[index] = m_advance[index - 1] + (c.advance >> 6);
			for (unsigned i = index + 1; i < m_string.size(); i++) {
				c = FontManager_M->GetCharacter(m_string[i], m_fontSize);
				MakeCharVerts(verts, c, m_advance[i], textureSize);
				m_advance[i] = m_advance[i - 1] + (c.advance >> 6);
			}
			m_buffer->EditData(index * sizeof(FontVertex) * 4, sizeof(FontVertex) * verts.size(), verts.data());
		}
	}

	void FontRenderable::AppendToBuffer(const std::string& str){
		m_string += str;
		MakeBuffer();
	}
	
	void FontRenderable::Render(Shader * shader){
		m_texture->Bind(0);
		shader->SetUniform("m", m_modelMatrix);
		m_buffer->Bind();
		m_indexBuffer->Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::FontVertex), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::FontVertex), (GLvoid*)sizeof(glm::vec3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::FontVertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
		glDrawElements(GL_TRIANGLES, (m_renderTo - m_renderFrom)* 6, GL_UNSIGNED_SHORT, (GLvoid*)(m_renderFrom * 6));
		CheckGLError();
	}

} }