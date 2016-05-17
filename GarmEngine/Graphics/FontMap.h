#pragma once
#include "Texture.h"
#include <map>

#define FONTMAP_SIZE 1024

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
	};

	class FontMap : public Texture {
		std::map<wchar_t, Character> m_characters;
		std::string m_fontPath;
		Character LoadCharacter(wchar_t c);
		unsigned short m_CurrentLineHeight{ 0 };
		glm::ivec2 m_NextPos{ 0.0f, 0.0f };
		void LoadCharacters(wchar_t begin, wchar_t end);
		FontMap(std::string path, short fontSize);
		short m_fontSize;
		friend class FontManager;
	public:
		const Character GetCharacter(wchar_t c);
	};

	class FontManager {
		FontManager() {}
		FontManager(const FontManager& r) {}
		static FontManager* m_instance;
		std::map<Fonts, std::map<short, FontMap*>> m_fontMaps;
	public:
		static void Init();
		static FontManager* GetInstance();
		FontMap* GetFontMap(Fonts fontType, short fontSize);
		Character GetCharacter(Fonts fontType, short fontSize, wchar_t c);
	};

#define FontManager_M garm::graphics::FontManager::GetInstance()

} }