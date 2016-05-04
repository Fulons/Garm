#include "Layer.h"
#include "Renderer.h"

namespace garm { namespace graphics {


	Simple2DLayer::Simple2DLayer(const glm::mat4 & projectionMatrix)
	: m_projectionMatrix(projectionMatrix), m_renderer(new Simple2DRenderer()){
		
	}
	Simple2DLayer::~Simple2DLayer(){
		delete m_renderer;
	}
}}