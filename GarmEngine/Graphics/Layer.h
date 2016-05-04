#pragma once
#include <glm/glm.hpp>
#include <vector>
namespace garm { namespace graphics {

	//contains renderer, renderables, proj matrix / camera, ~shader
	class Layer {
	private:
		bool m_Visible;

	public:
		Layer() {};
		virtual ~Layer() {};
		inline bool IsVisible() { return m_Visible; }
		inline bool SetVisible(bool visible) { m_Visible = visible; }

		virtual void Init() {};
		virtual void OnUpdate() {};
		virtual void OnRender() {};
	};

	class Shader;
	class Renderable2D;
	class Simple2DRenderer;

	class Simple2DLayer {
	private:
		Shader* m_shader;
		Simple2DRenderer* m_renderer;
		std::vector<Renderable2D*> m_Renderables;
		glm::mat4 m_projectionMatrix;
	public:
		Simple2DLayer(const glm::mat4& projectionMatrix);
		~Simple2DLayer();
		Shader* GetShader() { return m_shader; }

		void AddRenderable(Renderable2D* renderable);

		virtual void OnRender();
	};

} }