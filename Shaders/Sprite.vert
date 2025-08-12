#version 330 core

layout (location = 0) in vec2 aUV;

layout (location = 1) in mat3 iTrans;
layout (location = 4) in vec4 iColor;
layout (location = 5) in vec4 iTexCoord;

out vec4 vColor;
out vec2 vTexCoord;

uniform mat3 u_mProj;

void main() {
	gl_Position = vec4((vec3(aUV.x, aUV.y, 1.0) * iTrans * u_mProj).xy, 0.0, 1.0);
	vColor = iColor;
	vTexCoord = mix(iTexCoord.xy, iTexCoord.zw, aUV);
}