#include "TextRendering.h"
#include "Texture.h"
#include "Group2D.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

namespace garm { namespace graphics {

	

	Font::Character* Font::GetCharacter(char c){
		auto pos = m_characters.find(c);
		if (pos != m_characters.end()) return &pos->second;
		else {
			std::cout << "Unloaded char trying to be rendered" << std::endl;
			assert(false);
			return nullptr;
		}
	}

	Font::Font(std::string path)
	: m_path(path){
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "Could not init Freetype!" << std::endl;
		FT_Face face;
		if (FT_New_Face(ft, m_path.c_str(), 0, &face))
			std::cout << "Failed to load font: " << m_path << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);
		
		for (GLubyte c = 0; c < 128; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cout << "Failed to laod glyph" << std::endl;
				continue;
			}
			TextureOld* texture = new TextureOld(face->glyph->bitmap.buffer, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), 1);
			m_characters.insert(std::pair<char, Character>(
				c, {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					(GLuint)face->glyph->advance.x }));
		}
	}

	void Font::PutStringInGroup(std::string string, Group2D* group){
		glm::vec3 position(0.0f, 0.0f, 0.0f);
		for (char i = 0; i < string.length(); i++) {
			Character* character = GetCharacter(string[i]);
			Renderable2D* renderable = Renderable2D::MakeDefaultRenderable(character->texture, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
			renderable->setPosition(position);
			renderable->setScale(character->size);
			group->AddRenderable(renderable);
			position.x += (character->advance >> 6);
		}
	}

	StringRenderable::StringRenderable()
	: m_vb(GL_DYNAMIC_DRAW){
	//	m_vb.SetData()
	}
} }