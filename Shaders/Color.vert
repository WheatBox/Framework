#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 vColor;

uniform mat3 u_mProj;

void main() {
	gl_Position = vec4((vec3(aPos.x, aPos.y, 1.f) * u_mProj).xy, aPos.z, 1.f);
	vColor = aColor;
}