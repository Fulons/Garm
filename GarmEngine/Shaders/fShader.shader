#version 330 core

uniform vec2 mouse;
uniform sampler2D t;

out vec4 color;

in vec3 out_color;
in vec4 pos;
in vec2 texCoord;


void main() {
	float intensity = max(1.0f / length(pos.xy - mouse), 1.0f);
	//color = vec4(out_color, 1.0f) * intensity;
	color = texture(t, texCoord) * intensity;
}