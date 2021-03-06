#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Shader.h"

/////Console command class?
//must take a name++
//implement a way to notify on change
template <typename T>
	class EventVar{
		T var;
	public:

		template <typename T>
		operator T() const {
			return var;
		}

		T& operator .() {
			return var;
		}

		template <typename T>
		EventVar<T>& operator =(T value) {
			var = value;
			return *this;
		}
	};


namespace garm { namespace graphics {
	/*
	struct Vertex2D {
	
	};
	
	struct Vertex3D {

	};

	class Mesh2D {
		Vertex2D* m_verts;
		unsigned int m_numVerts;
		VertexArray* m_va;
	public:
		Mesh2D(Vertex2D* verts, unsigned int numVerts){}
		//render and if necessary create the vertexarray
	};

	class Mesh3D {
		Vertex3D* m_verts;
		unsigned int m_numVerts;
		VertexArray* m_va;
	public:
		Mesh3D(Vertex3D* verts, unsigned int numVerts){}
		//render and if necessary create the vertexarray
		void Render(){}
	};

	class Renderable2D {
		Mesh2D* m_mesh;
		glm::vec2 position;
		glm::quat rotation;
		glm::vec2 scale;
	public:
		Renderable2D(Mesh2D* mesh){}
		virtual void Render(Shader* shader){}
		
	};

	class Group2D : Renderable2D {
		std::vector<Mesh2D*> m_childMeshes;
	public:
		Group2D(Mesh2D* mesh) : Renderable2D(mesh){}
		void AddMesh(Mesh2D* mesh){}
		virtual void Render(Shader* shader) override{}
	};

	class Renderable3D {
		Mesh3D* m_mesh;
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
	public:
		Renderable3D(Mesh3D* mesh){}
		virtual void Render(Shader* shader){}
	};

	class Group3D : Renderable3D{
		std::vector<Mesh3D*> m_childMeshes;
	public:
		Group3D(Mesh3D* mesh) : Renderable3D(mesh){}
		void AddMesh(Mesh3D* mesh){}
		virtual void Render(Shader* shader) override{}
	};


	class Renderer2D {

	public:
		void Begin(){}
		//this is wrong! redesign have to work with groups + batchrendering!!!
		void Submit(Renderable2D* renderable){}
		void Render(){}
	};

	class Layer {
		
	public:		
		virtual void OnInit()	= 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
	};

	class Layer2D : public Layer {
		Renderer2D* m_renderer;
		std::vector<Renderable2D*> m_renderables;
		bool m_visible;
	public:
		Layer2D(Renderer2D* renderer){}
		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
	};


	class Scene {
		std::vector<Layer*> m_layers;
	public:
		void addLayer(Layer* layer) {}
		void OnInit()	{}
		void OnUpdate()	{}
		void OnRender()	{}
	};

	// Think a bit about font rendering
	void test() {
		Renderer2D* renderer = new Renderer2D;
		Layer2D* layer = new Layer2D(renderer);
		
		Scene* scene = new Scene();
		scene->addLayer(layer);
	}
	*/
} }

