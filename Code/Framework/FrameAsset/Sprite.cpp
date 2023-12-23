#include <FrameAsset/Sprite.h>
#include <FrameAsset/ErrorSprite.h>

#include <FrameCore/Log.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Frame {

	SSpriteImage::SSpriteImage(const unsigned char * data, int channel, int & refWidth, int & refHeight, Vec2 & refVOffset)
		: m_refWidth { refWidth }
		, m_refHeight { refHeight }
		, m_refVOffset { refVOffset }
	{
		m_textureId = Generate(data, channel, refWidth, refHeight);
	}

	SSpriteImage::~SSpriteImage() {
		glDeleteTextures(1, & m_textureId);
	}

	unsigned int SSpriteImage::Generate(const unsigned char * data, int channel, int width, int height) {
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
		glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		return resultTextureId;
	}

	CStaticSprite::CStaticSprite(const char * filename) {
		int channel;
		unsigned char * data = stbi_load(filename, & m_width, & m_height, & channel, 0);
		if(data) {
			m_pImage = new SSpriteImage { data, channel, m_width, m_height, m_vOffset };
		} else {
			Log::Log(Log::ELevel::Error, "Failed to load static sprite file: %s", filename);

			m_width = __errorSpriteDataWidth;
			m_height = __errorSpriteDataHeight;
			m_pImage = new SSpriteImage { __errorSpriteData, __errorSpriteDataChannel, m_width, m_height, m_vOffset };
		}
		stbi_image_free(data);
	}

	CStaticSprite::~CStaticSprite() {
		delete m_pImage;
	}

	CAnimatedSprite::CAnimatedSprite(const char * stripFilename, int frameCount) {
		if(frameCount <= 0) {
			Log::Log(Log::ELevel::Error, "Animated sprites' frame count (in this time, it is %d) can not be lower than 1. Filename: %s", frameCount, stripFilename);
			ConstructErrorImages();
			return;
		}

		int channel, stripWidth;
		unsigned char * data = stbi_load(stripFilename, & stripWidth, & m_height, & channel, 0);
		
		m_width = stripWidth / frameCount;
		
		if(data) {

			m_frameCount = frameCount;
			m_frames = new SSpriteImage * [frameCount];

			int stripWidthInByte = stripWidth * channel;
			int frameWidthInByte = m_width * channel;
			unsigned char * currentFrameData = new unsigned char[frameWidthInByte * m_height];

			for(int i = 0; i < frameCount; i++) {

				for(int _y = 0; _y < m_height; _y++) {
					for(int _x = 0; _x < frameWidthInByte; _x++) {
						currentFrameData[_y * frameWidthInByte + _x] = data[_y * stripWidthInByte + i * frameWidthInByte + _x];
					}
				}

				m_frames[i] = new SSpriteImage { currentFrameData, channel, m_width, m_height, m_vOffset };
			}

			delete[] currentFrameData;

		} else {
			Log::Log(Log::ELevel::Error, "Failed to load animated sprite file: %s", stripFilename);
			ConstructErrorImages();
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

	void CAnimatedSprite::ConstructErrorImages() {
		m_width = __errorSpriteDataWidth;
		m_height = __errorSpriteDataHeight;

		m_frameCount = 1;
		m_frames = new SSpriteImage * [1] {
			new SSpriteImage {
				__errorSpriteData,
				__errorSpriteDataChannel,
				m_width,
				m_height,
				m_vOffset
			}
		};
	}

}