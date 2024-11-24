#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

layout (location = 3) in mat3 aInsTrans;
layout (location = 6) in mat3 aInsTexTrans;
layout (location = 9) in vec4 aInsBlend;

out vec4 vColor;
out vec2 vTexCoord;

uniform mat3 u_mProj;

void main() {
	gl_Position = vec4((vec3(aPos.x, aPos.y, 1.f) * aInsTrans * u_mProj).xy, aPos.z, 1.f);
	vColor = aInsBlend * aColor;
	vTexCoord = (vec3(aTexCoord, 1.f) * aInsTexTrans).xy;
}