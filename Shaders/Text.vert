#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform vec2 u_vPos;
uniform mat3 u_mProj;

void main() {
	gl_Position = vec4((vec3(aPos.x + u_vPos.x, aPos.y + u_vPos.y, 1.f) * u_mProj).xy, aPos.z, 1.f);
	vTexCoord = aTexCoord;
}