#version 330 core

in layout(location = 0) vec3 position;
in layout(location = 1) vec4 color;
in layout(location = 2) vec3 UV;

uniform mat4 m, v, p;

out vec4 out_color;
out vec4 pos;
out vec2 texCoord;
flat out int textureID;

void main() {
	out_color = color;
	gl_Position = p * m * vec4(position, 1.0f);
	pos = m * vec4(position, 1.0f);
	texCoord = vec2(UV.xy);
	textureID = int(UV.z);
}