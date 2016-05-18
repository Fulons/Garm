#pragma once
#include "Shader.h"
#include "../Math.h"

#include <vector>

namespace garm { namespace graphics {

	class Renderer {

	public:
		virtual void Render(Shader* shader) = 0;
	};

} }