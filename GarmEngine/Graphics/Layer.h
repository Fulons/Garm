#pragma once


namespace garm { namespace graphics {

	//contains renderer, renderables, proj matrix / camera, ~shader
	// and most importantly glState like e.g depth range
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

} }