#pragma once

#include "Renderable.h"
#include "../Math.h"
#include "Buffer.h"
#include "Shader.h"
#include "FontMap.h"
#include <string>
#include <vector>

namespace garm{ namespace graphics{	

	struct FontVertex {
		FontVertex(const glm::vec3& pos, const glm::vec4& color, const glm::vec3& uv)
			: pos(pos), color(color), uv(uv){}
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec3 uv;
	};

	class Texture;
	class FontRenderable : public Renderable {
		std::string m_string;
		std::vector<glm::vec4> m_charColors;
		std::vector<unsigned> m_advance;
		Buffer* m_buffer = nullptr;
		Buffer* m_indexBuffer = nullptr;
		unsigned m_renderFrom, m_renderTo;
		const Texture* m_texture;

		short m_fontSize;

		std::string m_newString;
		bool m_newStringSet = false;
		bool m_colorsSet = false;
		bool m_fontSizeSet = false;

		void MakeBuffer();
		void MakeCharVerts(std::vector<FontVertex>& verts, const Character& c, unsigned advance, const glm::vec2& textureSize);
		void MakeCharIndices(std::vector<GLushort>& indices, unsigned index);
		void UpdateCharBuffer(unsigned index);
		void AppendToBuffer(const std::string& str);
	protected:
		FontRenderable();
	public:
		FontRenderable(const std::string& str, short fontSize, const std::vector<glm::vec4>& charColors);
		void SetString(const std::string& str);
		void SetColor(const std::vector<glm::vec4>& charColors);
		void SetFontSize(short fontSize);
		
		void RefreshBuffer();
		
		void PushBack(const std::string& str);
		void PopBack(unsigned n = 1);
		void PopFront(unsigned n = 1);
		virtual ~FontRenderable();

		virtual void Render(Shader* shader) override;
	};

} }