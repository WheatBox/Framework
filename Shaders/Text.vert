#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform vec2 u_vPos;
uniform vec2 u_vProj;
uniform vec2 u_vCamPos;
uniform float u_fViewRotRad;

void main() {
	vec2 pos = vec2(aPos.x + u_vPos.x - u_vCamPos.x, -aPos.y - u_vPos.y + u_vCamPos.y);
	float cosr = cos(u_fViewRotRad), sinr = sin(u_fViewRotRad);
	pos = vec2(pos.x * cosr - pos.y * sinr, pos.y * cosr + pos.x * sinr);
	gl_Position = vec4(pos.x * u_vProj.x, pos.y * u_vProj.y, aPos.z, 1.f);
	vTexCoord = aTexCoord;
}