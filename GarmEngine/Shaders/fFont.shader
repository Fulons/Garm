#version 330 core

uniform vec2 mouse;
uniform sampler2DArray t;

out vec4 color;

in vec4 out_color;
in vec4 pos;
in vec2 texCoord;
flat in int textureID;

void main() {
	float intensity = max(20.0f / length(pos.xy - mouse), 1.0f);

	color = vec4(out_color.xyz, texture(t, vec3(texCoord.xy, float(textureID))).r) * intensity;
}