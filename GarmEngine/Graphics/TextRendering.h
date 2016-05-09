#pragma once
#include "../Math.h"
#include <gl/glew.h>
#include <string>
#include <map>


namespace garm { namespace graphics {

	class Texture;
	class Group2D;
	class Font {
		struct Character {
			Texture* texture;
			glm::ivec2 size;
			glm::ivec2 bearing;
			GLuint advance;
		};
		std::map<char, Character> m_characters;
		Texture* GetCharTexture(char c);

	public:
		Font(std::string path);
		void PutStringInGroup(std::string string, Group2D* group);
	};

} }