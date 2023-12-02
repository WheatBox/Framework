#version 330 core

in vec2 vTexCoord;

uniform sampler2D u_BaseTexture;
uniform vec4 u_vColor;

void main() {
	gl_FragColor = vec4(u_vColor.r, u_vColor.g, u_vColor.b, u_vColor.a * texture(u_BaseTexture, vTexCoord).r);
}