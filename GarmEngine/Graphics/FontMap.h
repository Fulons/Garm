#pragma once
#include "Texture.h"
#include <map>

#define FONTMAP_SIZE 1024

typedef struct FT_FaceRec_*  FT_Face;
typedef struct FT_LibraryRec_  *FT_Library;
namespace garm { namespace graphics {

	enum Fonts {
		FONT_SCP_XL = 0,
		FONT_SCP_XL_I,
		FONT_SCP_L,
		FONT_SCP_L_I,
		FONT_SCP_R,
		FONT_SCP_R_I,
		FONT_SCP_M,
		FONT_SCP_M_I,
		FONT_SCP_SB,
		FONT_SCP_SB_I,
		FONT_SCP_B,
		FONT_SCP_B_I,
		FONT_SCP_XB,
		FONT_SCP_XB_I
	};


	namespace {
		static std::string G_FontPaths[] = {
			"Resources/Fonts/SourceCodePro-ExtraLight.ttf",
			"Resources/Fonts/SourceCodePro-ExtraLightIt.ttf",
			"Resources/Fonts/SourceCodePro-Light.ttf",
			"Resources/Fonts/SourceCodePro-LightIt.ttf",
			"Resources/Fonts/SourceCodePro-Regular.ttf",
			"Resources/Fonts/SourceCodePro-It.ttf",
			"Resources/Fonts/SourceCodePro-Medium.ttf",
			"Resources/Fonts/SourceCodePro-MediumIt.ttf",
			"Resources/Fonts/SourceCodePro-Semibold.ttf",
			"Resources/Fonts/SourceCodePro-SemiboldIt.ttf",
			"Resources/Fonts/SourceCodePro-Bold.ttf",
			"Resources/Fonts/SourceCodePro-BoldIt.ttf",
			"Resources/Fonts/SourceCodePro-Black.ttf",
			"Resources/Fonts/SourceCodePro-BlackIt.ttf",
		};
	}

	struct Character {
		glm::ivec2 pos;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
		unsigned short textureID;
	};

	//class FontMap : public TextureOld {
	//	std::map<wchar_t, Character> m_characters;
	//	std::string m_fontPath;
	//	Character LoadCharacter(wchar_t c);
	//	unsigned short m_CurrentLineHeight{ 0 };
	//	glm::ivec2 m_NextPos{ 0.0f, 0.0f };
	//	void LoadCharacters(wchar_t begin, wchar_t end);
	//	FontMap(std::string path, short fontSize);
	//	short m_fontSize;
	//	friend class FontManager;
	//public:
	//	const Character GetCharacter(wchar_t c);
	//};

	enum {
		FONT_LOAD_BOLD = 0x0001,
		FONT_LOAD_ITALIC = 0x0002,
		FONT_LOAD_BOLD_AND_ITALIC = FONT_LOAD_BOLD | FONT_LOAD_ITALIC,
	};

	class FontMap : public Texture2DArray {
		Fonts m_normalFont;
		short m_normalSize;
		std::vector<short> m_sizes;
		short m_flags;

		Character LoadChar(wchar_t c, FT_Face& face, unsigned mapIndex);
		bool LoadFont(FT_Library& library, FT_Face& face, const std::string& path);
		void LoadCharacters(wchar_t begin, wchar_t end);
		unsigned short FindClosestSizeIndex(short size);
		std::map<wchar_t, Character>* m_characters;
		std::vector<std::pair<glm::ivec2, unsigned short>> m_nextPos_lineHeight;

		const Character LoadCharacter(wchar_t c, short sizeIndex, short mapIndex, bool bold = false, bool italic = false);

		FontMap(Fonts normalFont, const std::vector<short>& sizes, short flags);
		friend class FontManager;
	public:
		const Character GetCharacter(wchar_t c, short hintSize, bool bold = false, bool italic = false);
		const std::map<wchar_t, Character>& GetCharMap(short hintSize, bool bold = false, bool italic = false);
	};

	class FontManager {
		FontManager() {}
		FontManager(const FontManager& r) {}
		static FontManager* m_instance;
		FontMap* m_fontMap;
	public:
		static void Init();
		static FontManager* GetInstance();
		Character GetCharacter(wchar_t c, short hintSize, bool bold = false, bool italic = false);
		const std::map<wchar_t, Character>& GetCharMap(short hintSize, bool bold = false, bool italic = false);
		glm::ivec2 GetTextureSize() { return m_fontMap->GetSize(); }
		const Texture* GetTexture() { return m_fontMap; }
	};



#define FontManager_M garm::graphics::FontManager::GetInstance()

} }