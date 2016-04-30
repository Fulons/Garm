#version 330 core


in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

uniform mat4 m, v, p;

out vec3 out_color;
out vec4 pos;

void main() {
	out_color = color;
	gl_Position = p * m * vec4(position, 1.0f);
	pos = m * vec4(position, 1.0f);
}