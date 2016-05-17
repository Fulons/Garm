#include "GUIRenderer.h"
#include "../Buffer.h"

#include <iostream>
#include <soil/SOIL.h>

namespace garm{ namespace graphics{

	BitmapFragmentMap::Fragment::~Fragment() {
		delete m_child[0];
		delete m_child[1];
	}

	BitmapFragmentMap::Fragment* BitmapFragmentMap::Fragment::Insert(glm::ivec2 size){
		Fragment* newNode;
		if (m_child[0] != nullptr && m_child[1] != nullptr) {	//not a leaf
			if (m_child[0] != nullptr) {
				if (newNode = m_child[0]->Insert(size))			//try to insert in first child
					return newNode;
				else return m_child[1]->Insert(size);			//try to insert in second child returns nullptr if unable to insert
			}
		}
		else {
			if (m_ID != 0) return nullptr;						//Leaf already containing image
			if (size.x > m_size.x || size.y > m_size.y) return nullptr;	//If leaf is to small
			if (size.x == m_size.x && size.y == m_size.y) return this;	//If perfect fit..we are done!

			//Node to large so have to split and create some children
			m_child[0] = new Fragment;
			m_child[1] = new Fragment;

			int deltaWidth = m_size.x - size.x;
			int deltaHeight = m_size.y - size.y;

			if (deltaWidth > deltaHeight) {
				m_child[0]->m_pos = m_pos;
				m_child[0]->m_size = glm::ivec2(size.x, m_size.y);

				m_child[1]->m_pos = glm::ivec2(m_pos.x + size.x, m_pos.y);
				m_child[1]->m_size = glm::ivec2(m_size.x - size.x, m_size.y);
			}
			else {
				m_child[0]->m_pos = m_pos;
				m_child[0]->m_size = glm::ivec2(m_size.x, size.y);

				m_child[1]->m_pos = glm::ivec2(m_pos.x, m_pos.y + size.y);
				m_child[1]->m_size = glm::ivec2(m_size.x, m_size.y - size.y);
			}
		}
		return m_child[0]->Insert(size);
	}

	//TODO: off by one error... 0 - 1024 in size...not sure if it resolves itself...think it actually does
	//if I ask for a size BITMAP_FRAMENT_MAP_SIZE texture to be inserted....
	BitmapFragmentMap::BitmapFragmentMap()
	: m_fragmentTree(glm::ivec2(BITMAP_FRAGMENT_MAP_SIZE, BITMAP_FRAGMENT_MAP_SIZE)){
		m_size = m_fragmentTree.GetSize();
		m_type = m_internalFormat = GL_RG;
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_size.x, m_size.y, 0, m_type, GL_UNSIGNED_BYTE, nullptr);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void BitmapFragmentMap::Insert(GLubyte* data, glm::ivec2 size, TextureFragmentType type){
		if (m_channels != 2) std::cout << "ERROR: expected 2 channeled texture!" << std::endl;
		m_channels = 2;
		Fragment* fragment = m_fragmentTree.Insert(size);
		if (fragment != nullptr) {
			EditTexture(fragment->GetPos(), data, size);
			fragment->SetID(type);
			m_fragments[type] = fragment;
		}
		else {
			//TODO: print error...
			assert(false);
		}
	}

	void BitmapFragmentMap::Insert(const std::string& path, TextureFragmentType type){
		glm::ivec2 size;
		int channels;
		GLubyte* data = SOIL_load_image(path.c_str(), &size.x, &size.y, &channels, SOIL_LOAD_AUTO);
		Insert(data, size, type);	//TODO: cannot use LoadDataFromFile funtion as it will set the size of the texture, just using atm for testing purposes
	}

	BitmapFragmentMap::Fragment* BitmapFragmentMap::Get(TextureFragmentType type){
		switch (type) {
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE_INVERSE:
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP:
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP_INVERSE:
			type = GUI_TEXTURE_FRAGMENT_TYPE_FADE;
			break;
		}
		auto ret = m_fragments.find(type);
		if (ret == m_fragments.end()) return nullptr;
		return ret->second;
	}

	void GUIRenderer::GetUV(std::vector<glm::vec2>& uv, TextureFragmentType type){
		BitmapFragmentMap::Fragment* texture = m_textureMap->Get(type);
		glm::vec2 uvPos = glm::vec2(texture->GetPos()) / glm::vec2(m_textureMap->GetSize());
		glm::vec2 uvSize = glm::vec2(texture->GetSize()) / glm::vec2(m_textureMap->GetSize());
		switch (type) {
		case GUI_TEXTURE_FRAGMENT_TYPE_COLOR:
			uv.insert(uv.end(), { uvPos, uvPos, uvPos, uvPos });
			break;
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE:
			//TODO: this might not work as expected as the size.x is 1
			uv.insert(uv.end(), { uvPos, uvPos + uvSize, uvPos + uvSize, uvPos });
			break;
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE_INVERSE:
			//TODO: this might not work as expected as the size.x is 1
			uv.insert(uv.end(), { uvPos + uvSize, uvPos, uvPos, uvPos + uvSize });
			break;
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP:
			//TODO: this might not work as expected as the size.x is 1
			uv.insert(uv.end(), { uvPos, uvPos, uvPos + uvSize, uvPos + uvSize });
			break;
		case GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP_INVERSE:
			//TODO: this might not work as expected as the size.x is 1
			uv.insert(uv.end(), { uvPos + uvSize, uvPos + uvSize, uvPos, uvPos });
			break;

		default:
			uv.insert(uv.end(), { uvPos, glm::vec2(uvPos.x + uvSize.x, uvPos.y), uvPos + uvSize, glm::vec2(uvPos.x, uvPos.y + uvSize.y) });
			break;
		}
	}

	GUIRenderer::GUIRenderer(){
		m_textureMap = new BitmapFragmentMap;
		GLubyte* fade = new GLubyte[512];
		for (unsigned i = 0; i < 256; i++) {
			fade[i * 2] = i;
			fade[i * 2 + 1] = 255;
		}
		m_textureMap->Insert(fade, glm::ivec2(256, 1), GUI_TEXTURE_FRAGMENT_TYPE_FADE);
		GLubyte color[] = { 255, 255 };
		m_textureMap->Insert(color, glm::ivec2(1, 1), GUI_TEXTURE_FRAGMENT_TYPE_COLOR);
		m_textureMap->Insert("Resources/GUIButtonClose.png", GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_CLOSE);
		m_textureMap->Insert("Resources/GUIButtonTHO.png", GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_TOGGLEHONLY);
		m_positionStack.emplace_back(0.0f, 0.0f);

		m_buffer = new Buffer(GUI_RENDERER_INITIAL_VBUFFER_SIZE, GL_DYNAMIC_DRAW);
		m_indexBuffer = new Buffer(GUI_RENDERER_INITIAL_IBUFFER_SIZE, GL_DYNAMIC_DRAW, nullptr, GL_ELEMENT_ARRAY_BUFFER);
		m_bufferSpriteCount = GUI_RENDERER_BUFFER_SPRITE_COUNT;
		SetupIndices();
	}

	void GUIRenderer::Render(Shader * shader){

	}

	void GUIRenderer::SetupIndices() {
		GLushort* m_mappedIndexBuffer = (GLushort*)m_indexBuffer->MapBufferWrite();

		for (unsigned i = 0; i < m_bufferSpriteCount; i++) {
			m_mappedIndexBuffer[i * 6 + 0] = i * 4 + 0;
			m_mappedIndexBuffer[i * 6 + 1] = i * 4 + 1;
			m_mappedIndexBuffer[i * 6 + 2] = i * 4 + 2;

			m_mappedIndexBuffer[i * 6 + 3] = i * 4 + 0;
			m_mappedIndexBuffer[i * 6 + 4] = i * 4 + 2;
			m_mappedIndexBuffer[i * 6 + 5] = i * 4 + 3;
		}
		m_indexBuffer->UnmapBuffer();
	}

	void GUIRenderer::Begin(){	
		m_mappedBuffer = (Vertex*)m_buffer->MapBufferWrite();
	}

	void GUIRenderer::AddSprite(const GUISprite& sprite){

		if (m_currentSpriteCount > m_bufferSpriteCount) {
			Flush();
			m_bufferSpriteCount += GUI_RENDERER_BUFFER_SPRITE_COUNT;
			delete m_buffer;
			m_buffer = new Buffer(m_bufferSpriteCount * GUI_RENDERER_SPRITE_VBUFFER_SIZE, GL_DYNAMIC_DRAW);
			delete m_indexBuffer;
			m_indexBuffer = new Buffer(m_bufferSpriteCount * GUI_RENDERER_SPRITE_IBUFFER_SIZE, GL_DYNAMIC_DRAW, nullptr, GL_ELEMENT_ARRAY_BUFFER);
			SetupIndices();

			Begin();
		}

		glm::ivec2 pos = m_positionStack.back();
		std::vector<glm::vec2> uv;
		GetUV(uv, sprite.type);

		m_mappedBuffer->color = sprite.color;
		m_mappedBuffer->position = glm::vec3(pos, 0.0f);
		m_mappedBuffer->UV = uv[0];
		m_mappedBuffer++;

		m_mappedBuffer->color = sprite.color;
		m_mappedBuffer->position = glm::vec3(pos.x + sprite.size.x, pos.y, 0.0f);
		m_mappedBuffer->UV = uv[1];
		m_mappedBuffer++;

		m_mappedBuffer->color = sprite.color;
		m_mappedBuffer->position = glm::vec3(pos.x + sprite.size.x, pos.y + sprite.size.y, 0.0f);
		m_mappedBuffer->UV = uv[2];
		m_mappedBuffer++;

		m_mappedBuffer->color = sprite.color;
		m_mappedBuffer->position = glm::vec3(pos.x, pos.y + sprite.size.y, 0.0f);
		m_mappedBuffer->UV = uv[3];
		m_mappedBuffer++;

		m_currentSpriteCount++;
	}

	void GUIRenderer::Flush(){
		m_textureMap->Bind(0);
		m_buffer->UnmapBuffer();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)sizeof(glm::vec3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(garm::graphics::Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
		
		glDrawElements(GL_TRIANGLES, m_currentSpriteCount * 6, GL_UNSIGNED_SHORT, nullptr);
	}

	void GUIRenderer::End(){
		Flush();
		m_currentSpriteCount = 0;
	}


	void GUIRenderer::PushPosition(glm::ivec2 pos){
		m_positionStack.push_back(m_positionStack.back() + pos);
	}

	void GUIRenderer::PopPosition(){
		if (m_positionStack.size() > 1)
			m_positionStack.pop_back();
	}

} }