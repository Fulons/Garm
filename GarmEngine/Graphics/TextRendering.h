#pragma once
#include "../Math.h"
#include "Renderable2D.h"
#include <gl/glew.h>
#include <string>
#include <map>

namespace garm { namespace graphics {

	class TextureOld;
	class Group2D;
	class Font {
		struct Character {
			TextureOld* texture;
			glm::ivec2 size;
			glm::ivec2 bearing;
			GLuint advance;
		};
		std::map<char, Character> m_characters;
		std::string m_path;

		Character* GetCharacter(char c);

	public:
		Font(std::string path);
		void PutStringInGroup(std::string string, Group2D* group);
	};
} }

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace garm { namespace graphics {

	class StringRenderable : public Renderable2D {
		std::string m_string;
		VertexBuffer m_vb;
	public:
		StringRenderable();
		//virtual void Render(Shader* shader) override;
	};

} }