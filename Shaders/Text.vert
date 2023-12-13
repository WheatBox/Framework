#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform vec2 u_vPos;
uniform vec2 u_vWindowSize;

void main() {
	gl_Position = vec4((aPos.x + u_vPos.x) * 2.f / u_vWindowSize.x - 1.f, -(aPos.y + u_vPos.y) * 2.f / u_vWindowSize.y + 1.f, aPos.z, 1.f);
	vTexCoord = aTexCoord;
}