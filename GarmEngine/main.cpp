
#include "Context/Context.h"
#include "Graphics/Shader.h"
#include "Context/InputHandler.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Mesh2D.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"
#include "Graphics/Layer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define _USE_MATH_DEFINES
#include <math.h>


class TestApp : public garm::Context {
public:
	TestApp(HINSTANCE hInstance);
	~TestApp(){}

	bool Init() override;
	void Update(float dt) override;
	void Render() override;
	//LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	garm::graphics::Shader* shader;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	TestApp app(hInstance);
	if (!app.Init())
		return 1;
	return app.Run();
	system("PAUSE");
	return 0;
}


TestApp::TestApp(HINSTANCE hInstance)
	: Context(hInstance){

}


garm::graphics::VertexBuffer* vb;
garm::graphics::IndexBuffer* ib;
garm::graphics::VertexArray* va;
garm::graphics::Mesh2D* mesh;
garm::graphics::Renderable2D* renderable;
garm::graphics::Renderable2D* renderable2;
garm::graphics::Renderable2D* renderable3;
garm::graphics::Renderable2D* renderable4;
garm::graphics::Simple2DRenderer* renderer;
garm::graphics::Simple2DLayer* layer;

bool TestApp::Init(){
	if (!Context::Init()) return false;
	shader = new garm::graphics::Shader("Shaders/vShader.shader", "Shaders/fShader.shader");
	shader->Use();
	garm::graphics::Vertex2D vertex[] = {
		{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
		glm::vec2()
		},{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
		glm::vec2()
		},{
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.9f, 1.0f),
		glm::vec2()
		},{
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
		glm::vec2()
		}
	};

	GLushort indices[] = {
		0, 1, 2,
		0, 2, 3
	};	

	//glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(400.0f, 300.0f, 0.0f));
	//glm::mat4 model = glm::scale(translation, glm::vec3(200, 200, 0.0f));
	glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f);
	shader->SetUniform("p", projection);

	ib = new garm::graphics::IndexBuffer(indices, 6);


	mesh = new garm::graphics::Mesh2D(vertex, 4, ib, true);
	renderable = new garm::graphics::Renderable2D(mesh);
	renderable->setPosition(glm::vec3(glm::vec3(1.0f, 1.0f, 0.0f)));
	
	renderable2 = new garm::graphics::Renderable2D(mesh);
	renderable2->setPosition(glm::vec3(glm::vec3(1.0f, -1.0f, 0.0f)));
	renderable3 = new garm::graphics::Renderable2D(mesh);
	renderable3->setPosition(glm::vec3(glm::vec3(-1.0f, 1.0f, 0.0f)));
	renderable4 = new garm::graphics::Renderable2D(mesh);
	renderable4->setPosition(glm::vec3(glm::vec3(-1.0f, -1.0f, 0.0f)));

	renderer = new garm::graphics::Simple2DRenderer;

	layer = new garm::graphics::Simple2DLayer(projection);
	layer->AddRenderable(renderable);
	layer->AddRenderable(renderable2);
	layer->AddRenderable(renderable3);
	layer->AddRenderable(renderable4);

	CheckGLError();
	glEnable(GL_DEPTH_TEST);
	return true;
}

void TestApp::Update(float dt){

}

void TestApp::Render() {
	glClearColor(0.05f, 0.075f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::vec2 mousepos(garm::InputHandler::GetMousePos().x, -garm::InputHandler::GetMousePos().y + GetClientHeight());
	mousepos.x /= GetClientWidth();
	mousepos.y /= GetClientHeight();
	renderable->rotate(glm::rotate(glm::quat(), 0.1f, glm::vec3(0.0f, 0.0f, 1.0f)));
	mousepos = (mousepos * glm::vec2(16.0f, 12.0f) - glm::vec2(8.0f, 6.0f));
	layer->GetShader()->SetUniform("mouse", mousepos);
	layer->OnRender();

	CheckGLError();
}