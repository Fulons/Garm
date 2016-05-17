#pragma once

#include "Renderable.h"
#include "../Math.h"
#include "Buffer.h"
#include "Shader.h"
#include <string>
#include <vector>

namespace garm{ namespace graphics{	
	class Texture;
	class FontRenderable : public Renderable {
		std::string m_string;
		std::vector<glm::vec4> m_charColors;
		Buffer* m_buffer = nullptr;
		Buffer* m_indexBuffer = nullptr;
		const Texture* m_texture;
		short m_fontSize;
		void MakeBuffer();
	protected:
		FontRenderable();
	public:
		FontRenderable(const std::string& str, short fontSize, const std::vector<glm::vec4>& charColors);
		virtual ~FontRenderable();

		virtual void Render(Shader* shader) override;
	};

} }