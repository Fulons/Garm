#pragma once
#include "../Renderer.h"
#include "../Texture.h"
#include <map>

#define BITMAP_FRAGMENT_MAP_SIZE 1024
#define GUI_RENDERER_BUFFER_SPRITE_COUNT 128
#define GUI_RENDERER_SPRITE_VBUFFER_SIZE sizeof(Vertex) * 4
#define GUI_RENDERER_INITIAL_VBUFFER_SIZE GUI_RENDERER_SPRITE_VBUFFER_SIZE * GUI_RENDERER_BUFFER_SPRITE_COUNT	//36 is size of vertex times 4 is size of sprite
#define GUI_RENDERER_SPRITE_IBUFFER_SIZE sizeof(GLushort) * 6
#define GUI_RENDERER_INITIAL_IBUFFER_SIZE GUI_RENDERER_SPRITE_IBUFFER_SIZE * GUI_RENDERER_BUFFER_SPRITE_COUNT	//2 is size of glushort, 6 indices per vertex

namespace garm { namespace graphics{

	enum TextureFragmentType {
		GUI_TEXTURE_FRAGMENT_TYPE_COLOR = 1,
		GUI_TEXTURE_FRAGMENT_TYPE_FADE,
		GUI_TEXTURE_FRAGMENT_TYPE_FADE_INVERSE,
		GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP,
		GUI_TEXTURE_FRAGMENT_TYPE_FADE_UP_INVERSE,	//maybe reserve a bit for flag to do inverse
		GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_CLOSE,
		GUI_TEXTURE_FRAGMENT_TYPE_BUTTON_TOGGLEHONLY,
	};

	//TODO: currently fragments contains artifacts of neighbouring fragments, need to have a border inbetween
	class BitmapFragmentMap : public Texture {
	public:
		class Fragment {
			Fragment* m_child[2];
			glm::ivec2 m_size;
			glm::ivec2 m_pos;
			int m_ID = 0;
			Fragment() { m_child[0] = m_child[1] = nullptr; }
		public:
			Fragment(glm::ivec2 size) : m_size(size){}
			~Fragment();
			inline const glm::ivec2& GetPos() { return m_pos; }
			inline const glm::ivec2& GetSize() { return m_size; }
			inline void SetID(int ID) { m_ID = ID; }
			Fragment* Insert(glm::ivec2 size);
		};

	private:
		Fragment m_fragmentTree;
		std::map<TextureFragmentType, Fragment*> m_fragments;

	public:
		BitmapFragmentMap();
		void Insert(GLubyte* data, glm::ivec2 size, TextureFragmentType type);
		void Insert(const std::string& path, TextureFragmentType type);
		Fragment* Get(TextureFragmentType type);
	};

	struct GUISprite {
		glm::vec2 size;
		TextureFragmentType type;
		glm::vec4 color;
	};

	class Buffer;

	class GUIRenderer : public Renderer {
		BitmapFragmentMap* m_textureMap;
		Buffer* m_buffer;
		Vertex* m_mappedBuffer;
		Buffer* m_indexBuffer;
		
		unsigned m_bufferSpriteCount;
		unsigned m_currentSpriteCount = 0;
		std::vector<glm::ivec2> m_positionStack;
		void GetUV(std::vector<glm::vec2>& uv, TextureFragmentType type);
		virtual void Flush();
		void SetupIndices();
	public:
		GUIRenderer();
		virtual void Render(Shader* shader) override{}
		virtual void Begin();
		virtual void AddSprite(const GUISprite& sprite);
		virtual void AddText(const std::string& text, const std::vector<glm::vec4>& colors);
		virtual void End();
		virtual void PushPosition(glm::ivec2 pos);
		virtual void PopPosition();
		//virtual void PushDepth();
		//virtual void PopDepth();
	};

} }