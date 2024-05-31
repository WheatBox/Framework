#pragma once

#define DEFAULT_SPRITE_SHADER_FILES \
	"./Shaders/Sprite.vert", "./Shaders/Sprite.frag"
#define DEFAULT_SPRITE_SHADER \
"#version 330 core\n \
layout (location = 0) in vec3 aPos; \
layout (location = 1) in vec4 aColor; \
layout (location = 2) in vec2 aTexCoord; \
out vec4 vColor; \
out vec2 vTexCoord; \
uniform vec2 u_vProj; \
uniform vec2 u_vCamPos; \
uniform float u_fViewRotRad;\
void main() {\
	vec2 pos = vec2(aPos.x - u_vCamPos.x, -aPos.y + u_vCamPos.y); \
	float cosr = cos(u_fViewRotRad), sinr = sin(u_fViewRotRad); \
	pos = vec2(pos.x * cosr - pos.y * sinr, pos.y * cosr + pos.x * sinr); \
	gl_Position = vec4(pos.x * u_vProj.x, pos.y * u_vProj.y, aPos.z, 1.f); \
	vColor = aColor; \
	vTexCoord = aTexCoord; \
}" \
, \
"#version 330 core\n \
in vec4 vColor; \
in vec2 vTexCoord; \
uniform sampler2D u_BaseTexture; \
void main() { \
	gl_FragColor = texture(u_BaseTexture, vTexCoord) * vColor; \
}"

#define DEFAULT_COLOR_SHADER_FILES \
	"./Shaders/Color.vert", "./Shaders/Color.frag"
#define DEFAULT_COLOR_SHADER \
"#version 330 core\n \
layout (location = 0) in vec3 aPos; \
layout (location = 1) in vec4 aColor; \
out vec4 vColor; \
uniform vec2 u_vProj; \
uniform vec2 u_vCamPos; \
uniform float u_fViewRotRad; \
void main() { \
	vec2 pos = vec2(aPos.x - u_vCamPos.x, -aPos.y + u_vCamPos.y); \
	float cosr = cos(u_fViewRotRad), sinr = sin(u_fViewRotRad); \
	pos = vec2(pos.x * cosr - pos.y * sinr, pos.y * cosr + pos.x * sinr); \
	gl_Position = vec4(pos.x * u_vProj.x, pos.y * u_vProj.y, aPos.z, 1.f); \
	vColor = aColor; \
}" \
, \
"#version 330 core\n \
in vec4 vColor; \
void main() { \
	gl_FragColor = vColor; \
}" \

#define DEFAULT_TEXT_SHADER_FILES \
	"./Shaders/Text.vert", "./Shaders/Text.frag"
#define DEFAULT_TEXT_SHADER \
"#version 330 core\n \
layout (location = 0) in vec3 aPos; \
layout (location = 1) in vec2 aTexCoord; \
out vec2 vTexCoord; \
uniform vec2 u_vPos; \
uniform vec2 u_vProj; \
uniform vec2 u_vCamPos; \
uniform float u_fViewRotRad; \
void main() { \
	vec2 pos = vec2(aPos.x + u_vPos.x - u_vCamPos.x, -aPos.y - u_vPos.y + u_vCamPos.y); \
	float cosr = cos(u_fViewRotRad), sinr = sin(u_fViewRotRad); \
	pos = vec2(pos.x * cosr - pos.y * sinr, pos.y * cosr + pos.x * sinr); \
	gl_Position = vec4(pos.x * u_vProj.x, pos.y * u_vProj.y, aPos.z, 1.f); \
	vTexCoord = aTexCoord; \
}" \
, \
"#version 330 core\n \
in vec2 vTexCoord; \
uniform sampler2D u_BaseTexture; \
uniform vec4 u_vColor; \
void main() { \
	gl_FragColor = vec4(u_vColor.r, u_vColor.g, u_vColor.b, u_vColor.a * texture(u_BaseTexture, vTexCoord).r); \
}"
