#include "FontMap.h"
#include <gl/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

namespace garm{ namespace graphics{

	Character FontMap::LoadCharacter(wchar_t c){
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "Could not init Freetype!" << std::endl;
		FT_Face face;
		if (FT_New_Face(ft, m_fontPath.c_str(), 0, &face))
			std::cout << "Failed to load font: " << m_fontPath << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);

		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
			std::cout << "Failed to load glyph: " << (char)c << " " << m_fontPath << std::endl;
		if (m_NextPos.x + (int)face->glyph->advance.x > m_size.x) {
			m_NextPos.y += m_CurrentLineHeight + 1;
			m_NextPos.x = 0;
			//TODO: check y bounds
		}
		Character ret{
			m_NextPos,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x };
		EditTexture(m_NextPos, face->glyph->bitmap.buffer, ret.size);
		m_CurrentLineHeight = m_CurrentLineHeight > ret.size.y ? m_CurrentLineHeight : ret.size.y;
		m_NextPos.x += ret.advance;
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		m_characters[c] = ret;
		return ret;
	}

	void FontMap::LoadCharacters(wchar_t begin, wchar_t end){
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "Could not init Freetype!" << std::endl;
		FT_Face face;
		if (FT_New_Face(ft, m_fontPath.c_str(), 0, &face))
			std::cout << "Failed to load font: " << m_fontPath << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);

		for (wchar_t c = begin; c <= end; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				std::cout << "Failed to load glyph: " << (char)c << " " << m_fontPath << std::endl;
			if (m_NextPos.x + (int)face->glyph->bitmap.width > m_size.x) {
				m_NextPos.y += m_CurrentLineHeight;
				m_NextPos.x = 0;
				//TODO: check y bounds
			}
			Character ret{
				m_NextPos,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(GLuint)face->glyph->advance.x };
			EditTexture(m_NextPos, face->glyph->bitmap.buffer, ret.size);
			m_CurrentLineHeight = m_CurrentLineHeight > ret.size.y ? m_CurrentLineHeight : ret.size.y;
			m_NextPos.x += ret.size.x;
			m_characters[c] = ret;
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		
	}

	FontMap::FontMap(std::string path)
	: m_fontPath(path){
		m_size = glm::ivec2(FONTMAP_SIZE, FONTMAP_SIZE);
		m_internalFormat = m_type = GL_RED;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_size.x, m_size.y, 0, m_type, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		LoadCharacters('!', '~');
	}

	const Character FontMap::GetCharacter(wchar_t c){
		auto it = m_characters.find(c);
		if (it != m_characters.end()) return it->second;
		return LoadCharacter(c);
	}

	FontManager* FontManager::m_instance = nullptr;

	void graphics::FontManager::Init(){
		if(m_instance == nullptr)
			m_instance = new FontManager();
		//TODO: ERROR?
	}

	FontManager* FontManager::GetInstance()
	{
		if (m_instance == nullptr)
		//TODO: ERROR?
			Init();
		
		return m_instance;

	}

	FontMap* FontManager::GetFontMap(Fonts fontType){
		auto it = m_fontMaps.find(fontType);
		if (it != m_fontMaps.end()) return it->second;
		FontMap* ret = new FontMap(G_FontPaths[fontType]);
		m_fontMaps[fontType] = ret;
		return ret;
	}

	Character FontManager::GetCharacter(Fonts fontType, wchar_t c){
		return GetFontMap(fontType)->GetCharacter(c);
	}
} }