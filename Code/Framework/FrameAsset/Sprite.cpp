#include <FrameAsset/Sprite.h>
#include <FrameAsset/ErrorSprite.h>

#include <FrameCore/Log.h>
#include <FrameRender/RendererBase.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Frame {

	unsigned int GenerateTexture(const unsigned char * data, int channel, const Vec2i & siz) {
		unsigned int resultTextureId;

		glGenTextures(1, & resultTextureId);
		RendererBase::BindTextureId(resultTextureId);

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
		glTexImage2D(GL_TEXTURE_2D, 0, mode, siz.x, siz.y, 0, mode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		return resultTextureId;
	}

	CTextureAtlas::CTextureAtlas(const char * filename, const std::unordered_map<std::string, std::pair<Vec2, Vec2>> & _uvs)
		: m_uvs { _uvs }
	{
		int channel;
		unsigned char * data = stbi_load(filename, & m_size.x, & m_size.y, & channel, 0);
		if(data) {
			m_textureId = GenerateTexture(data, channel, m_size);
		} else {
			Log::Log(Log::ELevel::Error, "Failed to load texture atlas file: %s", filename);

			m_size.x = __errorSpriteDataWidth;
			m_size.y = __errorSpriteDataHeight;
			m_textureId = GenerateTexture(__errorSpriteData, __errorSpriteDataChannel, m_size);
			for(auto & elem : m_uvs) {
				elem.second.first = { 0.f, 1.f };
				elem.second.second = { 1.f, 0.f };
			}
		}
		stbi_image_free(data);
	}

	CTextureAtlas::~CTextureAtlas() {
		glDeleteTextures(1, & m_textureId);
	}

	SSpriteImage::~SSpriteImage() {
		glDeleteTextures(1, & m_textureId);
	}

	CStaticSprite::CStaticSprite(const char * filename) {
		int channel;
		unsigned char * data = stbi_load(filename, & m_size.x, & m_size.y, & channel, 0);
		if(data) {
			m_pImage = new SSpriteImage { data, channel, m_size, m_vOffset };
		} else {
			Log::Log(Log::ELevel::Error, "Failed to load static sprite file: %s", filename);

			m_size.x = __errorSpriteDataWidth;
			m_size.y = __errorSpriteDataHeight;
			m_pImage = new SSpriteImage { __errorSpriteData, __errorSpriteDataChannel, m_size, m_vOffset };
		}
		stbi_image_free(data);
	}

	CStaticSprite::CStaticSprite(const CTextureAtlas * pTextureAtlas, const char * uvKey) {
		Vec2 uvLT { 0.f, 1.f };
		Vec2 uvRB { 1.f, 0.f };
		if(!pTextureAtlas || !pTextureAtlas->GetUV(& uvLT, & uvRB, uvKey)) {
			Log::Log(Log::ELevel::Error, "Failed to find static sprite uvKey: %s", uvKey);

			m_size.x = __errorSpriteDataWidth;
			m_size.y = __errorSpriteDataHeight;
			m_pImage = new SSpriteImage { __errorSpriteData, __errorSpriteDataChannel, m_size, m_vOffset };
			return;
		}

		m_size = Frame::Vec2i {
			static_cast<int>(std::round((uvRB.x - uvLT.x) * static_cast<float>(pTextureAtlas->GetSize().x))),
			static_cast<int>(std::round((uvLT.y - uvRB.y) * static_cast<float>(pTextureAtlas->GetSize().y)))
		};
		m_pImage = new SSpriteImage { pTextureAtlas->GetTextureId(), uvLT, uvRB, m_size, m_vOffset };
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
		unsigned char * data = stbi_load(stripFilename, & stripWidth, & m_size.y, & channel, 0);
		
		m_size.x = stripWidth / frameCount;
		
		if(data) {

			m_frameCount = frameCount;
			m_frames = new SSpriteImage * [frameCount];

			int stripWidthInByte = stripWidth * channel;
			int frameWidthInByte = m_size.x * channel;
			unsigned char * currentFrameData = new unsigned char[frameWidthInByte * m_size.y];

			for(int i = 0; i < frameCount; i++) {

				for(int _y = 0; _y < m_size.y; _y++) {
					for(int _x = 0; _x < frameWidthInByte; _x++) {
						currentFrameData[_y * frameWidthInByte + _x] = data[_y * stripWidthInByte + i * frameWidthInByte + _x];
					}
				}

				m_frames[i] = new SSpriteImage { currentFrameData, channel, m_size, m_vOffset };
			}

			delete[] currentFrameData;

		} else {
			Log::Log(Log::ELevel::Error, "Failed to load animated sprite file: %s", stripFilename);
			ConstructErrorImages();
		}
		stbi_image_free(data);
	}

	CAnimatedSprite::CAnimatedSprite(const CTextureAtlas * pTextureAtlas, std::initializer_list<const char *> uvKeys) {
		m_frameCount = static_cast<int>(uvKeys.size());
		m_frames = new SSpriteImage * [m_frameCount];

		bool bGotSize = false;

		int i = 0;
		for(auto & uvKey : uvKeys) {
			SSpriteImage * pImage;
			Vec2 uvLT { 0.f }, uvRB { 1.f };
			if(!pTextureAtlas || !pTextureAtlas->GetUV(& uvLT, & uvRB, uvKey)) {
				Log::Log(Log::ELevel::Error, "Failed to find animated sprite uvKey: %s", uvKey);

				Vec2i sizeTemp = m_size;
				m_size.x = __errorSpriteDataWidth;
				m_size.y = __errorSpriteDataHeight;
				pImage = new SSpriteImage { __errorSpriteData, __errorSpriteDataChannel, m_size, m_vOffset };
				m_size = sizeTemp;
			} else {
				if(!bGotSize) {
					bGotSize = true;
					m_size = Frame::Vec2i {
						static_cast<int>(std::round((uvRB.x - uvLT.x) * static_cast<float>(pTextureAtlas->GetSize().x))),
						static_cast<int>(std::round((uvLT.y - uvRB.y) * static_cast<float>(pTextureAtlas->GetSize().y)))
					};
				}
				pImage = new SSpriteImage { pTextureAtlas->GetTextureId(), uvLT, uvRB, m_size, m_vOffset };
			}
			m_frames[i++] = pImage;
		}

		if(!pTextureAtlas) {
			m_size.x = __errorSpriteDataWidth;
			m_size.y = __errorSpriteDataHeight;
		}
	}

	CAnimatedSprite::~CAnimatedSprite() {
		while(m_frameCount) {
			m_frameCount--;
			delete m_frames[m_frameCount];
		}
		delete[] m_frames;
	}

	void CAnimatedSprite::ConstructErrorImages() {
		m_size.x = __errorSpriteDataWidth;
		m_size.y = __errorSpriteDataHeight;

		m_frameCount = 1;
		m_frames = new SSpriteImage * [1] {
			new SSpriteImage {
				__errorSpriteData,
				__errorSpriteDataChannel,
				m_size,
				m_vOffset
			}
		};
	}

}