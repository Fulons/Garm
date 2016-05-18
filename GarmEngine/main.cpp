
#include "Context/Context.h"
#include "Graphics/Shader.h"
#include "Context/InputHandler.h"

//Soon to be removed?
//#include "Graphics/VertexArray.h"
//#include "Graphics/Mesh2D.h"
//#include "Graphics/Renderable2D.h"
//#include "Graphics/Renderer.h"
//#include "Graphics/Layer.h"
//#include "Graphics/Group2D.h"
//#include "Graphics/Texture.h"
//#include "Graphics/Simple2DLayer.h"
//#include "Graphics/TextRendering.h"

#include "Graphics/MeshData.h"
#include "Math.h"
#include "Graphics/FontRenderable.h"
#include "Graphics/FontMap.h"
#include "Graphics/GUI/Window.h"
#include "Graphics/GUI/GUIRenderer.h"
#include "Graphics/GUI/GUILayer.h"

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

garm::graphics::FontRenderable* fontRenderable;
garm::graphics::Buffer* ibuffer;
garm::graphics::Buffer* buffer;
garm::gui::Window* window;
garm::graphics::GUILayer* guiLayer;

GLuint VAO, VBO, IBO;

bool TestApp::Init(){
	if (!Context::Init()) return false;
	garm::graphics::FontManager::Init();
	CheckGLError();
	garm::graphics::Vertex verts[] = {
		{
			glm::vec3(0.0f, 0.0f, 0.1f),
			glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
			glm::vec2(0.0f, 1.0f)
		},{
			glm::vec3(500.0f, 0.0f, 0.1f),
			glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f)
		},{
			glm::vec3(500.0f, 500.0f, 0.1f),
			glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f)
		},{
			glm::vec3(0.0f, 500.0f, 0.1f),
			glm::vec4(0.9f, 0.0f, 0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		}
	};

	glm::mat4 m_projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.f);
	shader = new garm::graphics::Shader("Shaders/vFont.shader", "Shaders/fFont.shader");
	shader->Use();
	shader->SetUniform("p", m_projectionMatrix);
	shader->SetUniform("m", glm::translate(glm::mat4(1), glm::vec3(50.0f, 100.0f, 0.0f)));
	garm::graphics::MeshData mesh({ verts[0], verts[1], verts[2], verts[3] });
	mesh.GetIndexRef().insert(mesh.GetIndexRef().end(), { 0, 1, 2, 0, 2, 3 });
	buffer = mesh.MakeBuffer();
	ibuffer = mesh.MakeIndexBuffer();

	fontRenderable = new garm::graphics::FontRenderable("abcdefghijklmnopqrstu!~", 15, { glm::vec4(0.9f, 0.2f, 0.3f, 1.0f) });
	CheckGLError();
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	guiLayer = new garm::graphics::GUILayer(glm::ortho(0.0f, 800.0f, 0.0f, 600.f));
	window = new garm::gui::Window("Window", glm::ivec2(100, 100), glm::ivec2(200, 350), garm::gui::GUI_WINDOW_HEADER);
	guiLayer->AddWindow(window);



	return true;
}

void TestApp::Update(float dt){

}

void TestApp::Render() {
	CheckGLError();
	glClearColor(0.05f, 0.075f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();
	glm::vec2 mousepos(garm::InputHandler::GetMousePos().x, -garm::InputHandler::GetMousePos().y + GetClientHeight());
	shader->SetUniform("mouse", mousepos);
	fontRenderable->Render(shader);

	guiLayer->m_shader->Use();
	guiLayer->m_shader->SetUniform("mouse", mousepos);
	//guiLayer->OnRender();

	/*	// draw font texture onto screen, remember to manually set texture depth in shader
	shader->Use();
	FontManager_M->GetTexture()->Bind(0);

	buffer->Bind();
	ibuffer->Bind();
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
	shader->SetUniform("m", glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f)));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	*/
	CheckGLError();
	//shader->SetUniform("t", 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

}