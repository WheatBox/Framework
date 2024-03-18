#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vColor;
out vec2 vTexCoord;

uniform vec2 u_vProj;
uniform vec2 u_vCamPos;

void main() {
	gl_Position = vec4((aPos.x - u_vCamPos.x) * u_vProj.x, (-aPos.y + u_vCamPos.y) * u_vProj.y, aPos.z, 1.f);
	vColor = aColor;
	vTexCoord = aTexCoord;
}