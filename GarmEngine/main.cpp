
#include "Context/Context.h"
#include "Graphics/Shader.h"
#include "Context/InputHandler.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Mesh2D.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"
#include "Graphics/Layer.h"
#include "Graphics/Group2D.h"
#include "Graphics/Texture.h"
#include "Graphics/Simple2DLayer.h"
//#include "Graphics/TextRendering.h"
#include "Graphics/MeshData.h"
#include "Math.h"
#include "Graphics/FontRenderable.h"
#include "Graphics/FontMap.h"

#include <iostream>

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
garm::graphics::Group2D* renderable;
garm::graphics::Renderable2D* renderable2;
garm::graphics::Renderable2D* renderable3;
garm::graphics::Renderable2D* renderable4;
garm::graphics::Simple2DRenderer* renderer;
garm::graphics::Simple2DLayer* layer;
garm::graphics::Texture* texture;
//garm::graphics::Font* font;
garm::graphics::FontRenderable* fontRenderable;
garm::graphics::Buffer* buffer;

GLuint VAO, VBO, IBO;

bool TestApp::Init(){
	if (!Context::Init()) return false;
	garm::graphics::FontManager::Init();
#if 0
	font = new garm::graphics::Font("Resources/Fonts/SourceSansPro-Light.ttf");

	garm::graphics::Vertex vertex[] = {
		{
		glm::vec3(-50.0f, -50.0f, -0.1f),
		glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
		},{
		glm::vec3(50.0f, -50.0f, -0.1f),
		glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)
		},{
		glm::vec3(50.0f, 50.0f, -0.1f),
		glm::vec4(0.0f, 0.0f, 0.9f, 1.0f),
		glm::vec2(1.0f, 1.0f)
		},{
		glm::vec3(-50.0f, 50.0f, -0.1f),
		glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
		}
	};

	GLushort indices[] = {
		0, 1, 2,
		0, 2, 3
	};	

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.f);

	ib = new garm::graphics::IndexBuffer(indices, 6);

	texture = new garm::graphics::Texture("Textures/dot.png");
	mesh = new garm::graphics::Mesh2D(vertex, 4, ib, true);
	renderable = new garm::graphics::Group2D(mesh, texture);
	renderable->setPosition(glm::vec3(glm::vec3(400.0f, 300.0f, 0.0f)));
	//renderable->setScale(glm::vec2(300.0f, 300.0f));

	renderable2 = new garm::graphics::Renderable2D(mesh, texture);
	renderable2->setPosition(glm::vec3(glm::vec3(200.0f, -200.0f, 0.0f)));
	//renderable2->setScale(glm::vec2(100.0f, 100.0f));
	renderable3 = new garm::graphics::Renderable2D(mesh, texture);
	renderable3->setPosition(glm::vec3(glm::vec3(-200.0f, 200.0f, 0.0f)));
	//renderable3->setScale(glm::vec2(100.0f, 100.0f));
	renderable4 = new garm::graphics::Renderable2D(mesh, texture);
	renderable4->setPosition(glm::vec3(glm::vec3(-200.0f, -200.0f, 0.0f)));
	//renderable4->setScale(glm::vec2(100.0f, 100.0f));
	
	layer = new garm::graphics::Simple2DLayer(projection);
	layer->AddRenderable(renderable);
	font->PutStringInGroup("blaBLA", renderable);
	renderable->AddRenderable(renderable2);
	renderable->AddRenderable(renderable3);
	renderable->AddRenderable(renderable4);
	//layer->AddRenderable(renderable2);
	//layer->AddRenderable(renderable3);
	//layer->AddRenderable(renderable4);

	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#elseif 0

	garm::graphics::Vertex vertex[] = {
		{
			glm::vec3(-1.0f, -1.0f, -0.1f),
			glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		},{
			glm::vec3(1.0f, -1.0f, -0.1f),
			glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f)
		},{
			glm::vec3(1.0f, 1.0f, -0.1f),
			glm::vec4(0.0f, 0.0f, 0.9f, 1.0f),
			glm::vec2(1.0f, 1.0f)
		},{
			glm::vec3(-1.0f, 1.0f, -0.1f),
			glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
			glm::vec2(0.0f, 1.0f)
		}
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(garm::graphics::Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(garm::graphics::Vertex), (GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(garm::graphics::Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	CheckGLError();

#else
	garm::graphics::Vertex verts[] = {
		{
			glm::vec3(0.0f, 0.0f, -0.1f),
			glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
			glm::vec2(0.0f, 1.0f)
		},{
			glm::vec3(500.0f, 500.0f, -0.1f),
			glm::vec4(0.0f, 0.9f, 0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f)
		},{
			glm::vec3(0.0f, 500.0f, -0.1f),
			glm::vec4(0.0f, 0.0f, 0.9f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		}
	};

	glm::mat4 m_projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.f);
	shader = new garm::graphics::Shader("Shaders/vShader.shader", "Shaders/fShader.shader");
	shader->Use();
	shader->SetUniform("p", m_projectionMatrix);
	shader->SetUniform("m", glm::mat4(1));
	garm::graphics::MeshData mesh({ verts[0], verts[1], verts[2] });
	buffer =  mesh.MakeBuffer();
	
	
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)sizeof(glm::vec3));
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
	fontRenderable = new garm::graphics::FontRenderable("!heiSaanN!", { glm::vec4(0.9f, 0.2f, 0.3f, 1.0f) });
	//garm::graphics::FontMap* fm = FontManager_M->GetFontMap(garm::graphics::Fonts::FONT_SCP_R);
	//fm->Bind(0);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	return true;
}

void TestApp::Update(float dt){

}

void TestApp::Render() {
	glClearColor(0.05f, 0.075f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if 0
	if(garm::InputHandler::IsKeyDown(VK_SPACE))
		renderable->rotate(glm::rotate(glm::quat(), 0.001f, glm::vec3(0.0f, 0.0f, 1.0f)));
	if (garm::InputHandler::IsKeyDown(VK_RETURN))
		renderable->setRotation(glm::quat());
	//std::cout << "X: " << mousepos.x << " Y: " << mousepos.y << std::endl;
	//mousepos = (mousepos * glm::vec2(16.0f, 12.0f) - glm::vec2(8.0f, 6.0f));
	layer->GetShader()->SetUniform("mouse", mousepos);
	layer->GetShader()->SetUniform("t", 0);
	layer->OnRender();
#elseif 0
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	CheckGLError();
#else
	glm::vec2 mousepos(garm::InputHandler::GetMousePos().x, -garm::InputHandler::GetMousePos().y + GetClientHeight());
	shader->SetUniform("mouse", mousepos);
	fontRenderable->Render(shader);
	//shader->SetUniform("t", 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
}