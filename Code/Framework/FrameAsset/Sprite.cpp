#include <FrameAsset/Sprite.h>
#include <FrameAsset/ErrorSprite.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Frame {

	unsigned int ISprite::Generate(const unsigned char * pData, int channel, int width, int height) {
		unsigned int resultTextureId;

		glGenTextures(1, & resultTextureId);
		glBindTexture(GL_TEXTURE_2D, resultTextureId);

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
		glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, pData);
		glGenerateMipmap(GL_TEXTURE_2D);

		return resultTextureId;
	}

	CStaticSprite::CStaticSprite(const char * filename)
		: ISprite { m_width, m_height, m_vOffset }
	{
		int channel;
		unsigned char * data = stbi_load(filename, & m_width, & m_height, & channel, 0);
		if(data) {
			m_textureId = Generate(data, channel, m_width, m_height);
		} else {
			// TODO - 错误提示
			m_width = __errorSpriteDataWidth;
			m_height = __errorSpriteDataHeight;
			m_textureId = Generate(__errorSpriteData, __errorSpriteDataChannel, __errorSpriteDataWidth, __errorSpriteDataHeight);
		}
		stbi_image_free(data);
	}

	CStaticSprite::~CStaticSprite() {
		glDeleteTextures(1, & m_textureId);
	}

	CAnimatedSprite::CAnimatedSprite(const char * stripFilename, int frameCount)
		: ISprite { m_width, m_height, m_vOffset }
	{
		if(frameCount <= 0) {
			// TODO - 错误提示
			ConstructErrorSprites();
			return;
		}

		int channel, stripWidth;
		unsigned char * data = stbi_load(stripFilename, & stripWidth, & m_height, & channel, 0);
		
		m_width = stripWidth / frameCount;
		
		if(data) {

			m_frameCount = frameCount;
			m_frames = new CStaticSprite * [frameCount];

			int stripWidthInByte = stripWidth * channel;
			int frameWidthInByte = m_width * channel;
			unsigned char * currentFrameData = new unsigned char[frameWidthInByte * m_height];

			for(int i = 0; i < frameCount; i++) {

				for(int _y = 0; _y < m_height; _y++) {
					for(int _x = 0; _x < frameWidthInByte; _x++) {
						currentFrameData[_y * frameWidthInByte + _x] = data[_y * stripWidthInByte + i * frameWidthInByte + _x];
					}
				}

				m_frames[i] = new CStaticSprite { Generate(currentFrameData, channel, m_width, m_height), m_width, m_height, m_vOffset };
			}

			delete[] currentFrameData;

		} else {
			// TODO - 错误提示
			ConstructErrorSprites();
		}
		stbi_image_free(data);
	}

	CAnimatedSprite::~CAnimatedSprite() {
		while(m_frameCount) {
			m_frameCount--;
			delete m_frames[m_frameCount];
		}
		delete[] m_frames;
	}

	void CAnimatedSprite::ConstructErrorSprites() {
		m_width = __errorSpriteDataWidth;
		m_height = __errorSpriteDataHeight;

		m_frameCount = 1;
		m_frames = new CStaticSprite * [1] {
			new CStaticSprite {
				Generate(__errorSpriteData, __errorSpriteDataChannel, __errorSpriteDataWidth, __errorSpriteDataHeight),
				m_width,
				m_height,
				m_vOffset
			}
		};
	}

}