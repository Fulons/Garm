#version 330 core

uniform vec2 mouse;

out vec4 color;

in vec3 out_color;
in vec4 pos;


void main() {
	float intensity = max(1.0f / length(pos.xy - mouse), 1.0f);
	color = vec4(out_color, 1.0f) * intensity;
}