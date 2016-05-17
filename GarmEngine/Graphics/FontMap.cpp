#include "FontMap.h"
#include <gl/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

namespace garm{ namespace graphics{

#define _C_F(flag, flags) ((flag & flags) == flag)
#define CALCULATE_TEXTURE_DEPTH(flag, numsizes) \
	( _C_F(FONT_LOAD_BOLD, flag) ? \
		(_C_F(FONT_LOAD_ITALIC, flag) ? numsizes * 4 : numsizes * 2) \
	: (_C_F(FONT_LOAD_ITALIC, flag) ? numsizes * 2 : numsizes) )

	/*
	Character FontMap::LoadCharacter(wchar_t c){
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "Could not init Freetype!" << std::endl;
		FT_Face face;
		if (FT_New_Face(ft, m_fontPath.c_str(), 0, &face))
			std::cout << "Failed to load font: " << m_fontPath << std::endl;

		FT_Set_Pixel_Sizes(face, 0, m_fontSize);

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

		FT_Set_Pixel_Sizes(face, 0, m_fontSize);

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

	FontMap::FontMap(std::string path, short fontSize)
	: m_fontPath(path), m_fontSize(fontSize){
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
	}*/



	FontMap::FontMap(Fonts normalFont, const std::vector<short>& sizes, short flags)
	:Texture2DArray(glm::ivec3(FONTMAP_SIZE, FONTMAP_SIZE, CALCULATE_TEXTURE_DEPTH(flags, sizes.size())), GL_RED, 1), m_sizes(sizes), m_flags(flags){
		if ((normalFont & 1) == 1) m_normalFont = (Fonts)(normalFont + 1);
		else m_normalFont = normalFont;

		m_characters = new std::map<wchar_t, Character>[m_depth];
		for (unsigned short i = 0; i < m_depth; i++)
			m_nextPos_lineHeight.push_back(std::make_pair<glm::ivec2, unsigned short>(glm::ivec2(0, 0), 0));
		LoadCharacters('!', '~');
	}	

	Character FontMap::LoadChar(wchar_t c, FT_Face& face, unsigned mapIndex) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "Failed to load glyph: " << (char)c << "\n" << std::endl;
			return Character();
		}
		if (m_nextPos_lineHeight[mapIndex].first.x + (int)face->glyph->bitmap.width > m_size.x) {
			m_nextPos_lineHeight[mapIndex].first.y += m_nextPos_lineHeight[mapIndex].second;
			m_nextPos_lineHeight[mapIndex].first.x = 0;
			//TODO: check y bounds
		}
		Character ret{
			m_nextPos_lineHeight[mapIndex].first,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x,
			(unsigned short)mapIndex
		};
		BufferSubData(face->glyph->bitmap.buffer, glm::ivec3(m_nextPos_lineHeight[mapIndex].first, mapIndex), glm::ivec3(ret.size, 1));
		m_nextPos_lineHeight[mapIndex].second = m_nextPos_lineHeight[mapIndex].second > m_nextPos_lineHeight[mapIndex].first.y ? m_nextPos_lineHeight[mapIndex].second : m_nextPos_lineHeight[mapIndex].first.y;
		m_nextPos_lineHeight[mapIndex].first.x += ret.size.x;
		m_characters[mapIndex][c] = ret;
		return ret;
	}

	bool FontMap::LoadFont(FT_Library& library, FT_Face& face, const std::string& path) {
		if (FT_New_Face(library, path.c_str(), 0, &face)) {
			std::cout << "Failed to load font: " << path << std::endl;
			assert(false);	//TODO: something
			return false;
		}
		return true;
	}

	void FontMap::LoadCharacters(wchar_t begin, wchar_t end){
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cout << "Could not init Freetype!" << std::endl;
			return;
		}
		FT_Face face = 0;

		//Always load regular font
		LoadFont(ft, face, G_FontPaths[m_normalFont + 2]);
		for (unsigned size = 0; size < m_sizes.size(); size++) {
			FT_Set_Pixel_Sizes(face, 0, m_sizes[size]);
			for (wchar_t c = begin; c <= end; c++)
				LoadChar(c, face, size);
		}

		if (_C_F(FONT_LOAD_BOLD_AND_ITALIC, m_flags)) {
			//Load Bold font
			LoadFont(ft, face, G_FontPaths[m_normalFont + 2]);
			for (unsigned size = 0; size < m_sizes.size(); size++) {
				FT_Set_Pixel_Sizes(face, 0, m_sizes[size]);
				for (wchar_t c = begin; c <= end; c++)
					LoadChar(c, face, m_sizes.size() + size);
			}

			//Load italic font
			LoadFont(ft, face, G_FontPaths[m_normalFont + 1]);
			for (unsigned size = 0; size < m_sizes.size(); size++) {
				FT_Set_Pixel_Sizes(face, 0, m_sizes[size]);
				for (wchar_t c = begin; c <= end; c++)
					LoadChar(c, face, m_sizes.size() * 2 + size);
			}

			//Load bold italic font
			LoadFont(ft, face, G_FontPaths[m_normalFont + 3]);
			for (unsigned size = 0; size < m_sizes.size(); size++) {
				FT_Set_Pixel_Sizes(face, 0, m_sizes[size]);
				for (wchar_t c = begin; c <= end; c++)
					LoadChar(c, face, m_sizes.size() * 3 + size);
			}
		}
		else if (_C_F(FONT_LOAD_BOLD, m_flags)) {
			LoadFont(ft, face, G_FontPaths[m_normalFont + 2]);
			for (unsigned size = 0; size < m_sizes.size(); size++) {
				FT_Set_Pixel_Sizes(face, 0, m_sizes[size]);
				for (wchar_t c = begin; c <= end; c++)
					LoadChar(c, face, m_sizes.size() + size);
			}
		}
		else if (_C_F(FONT_LOAD_ITALIC, m_flags)) {
			LoadFont(ft, face, G_FontPaths[m_normalFont + 2]);
			for (unsigned size = 0; size < m_sizes.size(); size++) {
				FT_Set_Pixel_Sizes(face, 0, m_sizes[size]);
				for (wchar_t c = begin; c <= end; c++)
					LoadChar(c, face, m_sizes.size() + size);
			}
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

	}

	unsigned short FontMap::FindClosestSizeIndex(short size){
		short current = 0;
		short lastSize = 0xff;
		for (unsigned i = 0; i < m_sizes.size(); i++) {
			short deltaSize = abs(m_sizes[i] - size);
			if (deltaSize == 0) return i;
			if (deltaSize < lastSize) current = i;
		}
		return current;
	}

	const Character FontMap::LoadCharacter(wchar_t c, short sizeIndex, short mapIndex, bool bold, bool italic) {
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cout << "Could not init Freetype!" << std::endl;
			return Character();
		}
		FT_Face face = 0;
		short pathIndex = m_normalFont;
		if (bold && italic) { pathIndex += 3; }
		else if (bold) { pathIndex += 2;  }
		else if (italic) { pathIndex += 1; }
		LoadFont(ft, face, G_FontPaths[pathIndex]);
		FT_Set_Pixel_Sizes(face, 0, m_sizes[sizeIndex]);
		return LoadChar(c, face, mapIndex);

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	const Character FontMap::GetCharacter(wchar_t c, short hintSize, bool bold, bool italic)
	{
		short sizeIndex = FindClosestSizeIndex(hintSize);
		unsigned index = -1;
		if (!bold && !italic) {
			index = sizeIndex;
		}
		else if (bold && italic) {
			if(_C_F(FONT_LOAD_BOLD_AND_ITALIC, m_flags))
				index = sizeIndex + m_sizes.size() * 3;
		}
		else if(bold){
			if(_C_F(FONT_LOAD_BOLD, m_flags))
				index = sizeIndex + m_sizes.size();
		}
		else if (italic) {
			if (_C_F(FONT_LOAD_ITALIC, m_flags)) {
				if (_C_F(FONT_LOAD_BOLD, m_flags))
					index = sizeIndex + m_sizes.size() * 2;
				else index = sizeIndex + m_sizes.size();
			}
		}
		if (index == -1) {
			return Character();
			assert(false);	//TODO: print and log error
		}
		auto character = m_characters[index].find(c);
		if (character == m_characters[index].end()) return LoadCharacter(c, sizeIndex, index, bold, italic);
		else return character->second;
	}

	const std::map<wchar_t, Character>& FontMap::GetCharMap(short hintSize, bool bold, bool italic)
	{
		short sizeIndex = FindClosestSizeIndex(hintSize);
		unsigned index = -1;
		if (!bold && !italic) {
			index = sizeIndex;
		}
		else if (bold && italic) {
			if(_C_F(FONT_LOAD_BOLD_AND_ITALIC, m_flags))
				index = sizeIndex + m_sizes.size() * 3;
		}
		else if(bold){
			if(_C_F(FONT_LOAD_BOLD, m_flags))
				index = sizeIndex + m_sizes.size();
		}
		else if (italic) {
			if (_C_F(FONT_LOAD_ITALIC, m_flags)) {
				if (_C_F(FONT_LOAD_BOLD, m_flags))
					index = sizeIndex + m_sizes.size() * 2;
				else index = sizeIndex + m_sizes.size();
			}
		}
		if (index == -1) {
			return m_characters[0];
		}
		return m_characters[index];
	}

	/////////////////////////////////////////////////////////////

	FontManager* FontManager::m_instance = nullptr;

	void graphics::FontManager::Init(){
		if(m_instance == nullptr)
			m_instance = new FontManager();
		m_instance->m_fontMap = new FontMap(FONT_SCP_M, { 8, 12, 16, 20, 24, 48 }, FONT_LOAD_BOLD_AND_ITALIC);
		//TODO: ERROR?
	}

	FontManager* FontManager::GetInstance()
	{
		if (m_instance == nullptr)
		//TODO: ERROR?
			Init();
		
		return m_instance;

	}

	Character FontManager::GetCharacter(wchar_t c, short hintSize, bool bold, bool italic){
		return m_fontMap->GetCharacter(c, hintSize, bold, italic);
	}

	const std::map<wchar_t, Character>& FontManager::GetCharMap(short hintSize, bool bold, bool italic){
		return m_fontMap->GetCharMap(hintSize, bold, italic);
	}

} }