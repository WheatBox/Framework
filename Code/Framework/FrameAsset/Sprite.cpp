#include <FrameAsset/Sprite.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Frame {

	CStaticSprite::CStaticSprite(const char * filename) {
		stbi_set_flip_vertically_on_load(true);
		int channel = 0;
		unsigned char * pData = stbi_load(filename, & m_width, & m_height, & channel, 0);
		if(pData) {
			Generate(pData, channel);
		} else {
			// TODO - 错误提示
		}
		stbi_image_free(pData);
	}

	CStaticSprite::~CStaticSprite() {
		glDeleteTextures(1, & m_textureId);
	}

	void CStaticSprite::Generate(unsigned char * pData, int channel) {
		glGenTextures(1, & m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int mode = GL_RGBA;
		switch(channel) {
		case 3:
			mode = GL_RGB;
			break;
		case 4:
			mode = GL_RGBA;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, mode, m_width, m_height, 0, mode, GL_UNSIGNED_BYTE, pData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

}