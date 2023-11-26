#version 330 core

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D u_BaseTexture;

void main() {
	gl_FragColor = texture(u_BaseTexture, vTexCoord) * vColor;
}