
#include "Context/Context.h"
#include "Graphics/Shader.h"
#include "Context/InputHandler.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Mesh2D.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


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

	glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(400.0f, 300.0f, 0.0f));
	glm::mat4 model = glm::scale(translation, glm::vec3(200, 200, 0.0f));
	glm::mat4 projection = glm::ortho(0.0f, (float)GetClientWidth(), 0.0f, (float)GetClientHeight());
	shader->SetUniform("m", model);
	shader->SetUniform("p", projection);
	vb = new garm::graphics::VertexBuffer(GL_STATIC_DRAW);
	ib = new garm::graphics::IndexBuffer(indices, 6);
	garm::graphics::BufferAttribLayout layout;
	layout.Push<glm::vec3>("Position");
	layout.Push<glm::vec4>("Color");
	layout.Push<glm::vec2>("UV");
	vb->SetData(sizeof(vertex), vertex, layout);
	va = new garm::graphics::VertexArray(vb, ib);

	mesh = new garm::graphics::Mesh2D(vertex, 4, ib, true);
	CheckGLError();
	
	return true;
}

void TestApp::Update(float dt){

}

void TestApp::Render() {
	glClearColor(0.05f, 0.075f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->SetUniform("mouse", glm::vec2(garm::InputHandler::GetMousePos().x, -garm::InputHandler::GetMousePos().y + GetClientHeight()));
	mesh->Render();
	CheckGLError();
}