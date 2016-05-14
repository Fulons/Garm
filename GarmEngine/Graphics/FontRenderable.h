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
		Texture* m_texture;
		void MakeBuffer();
	public:
		FontRenderable();
		FontRenderable(const std::string& str);
		FontRenderable(const std::string& str, const std::vector<glm::vec4> charColors);
		~FontRenderable();

		virtual void Render(Shader* shader) override;
	};

} }