#version 330 core

uniform vec2 mouse;
uniform sampler2D t;

out vec4 color;

in vec4 out_color;
in vec4 pos;
in vec2 texCoord;


void main() {
	float intensity = max(20.0f / length(pos.xy - mouse), 1.0f);
	//color = out_color *intensity;
	//color = vec4(out_color.xyz, texture(t, texCoord).r) * intensity;
	vec4 tex_color = texture(t, texCoord).rrrg;
	color = out_color * vec4(tex_color.rrr * intensity, tex_color.a);
}