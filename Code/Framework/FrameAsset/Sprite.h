#pragma once

#include <FrameMath/Vector2.h>
#include <FrameMath/ColorMath.h>

#include <unordered_map>
#include <string>

namespace Frame {

	unsigned int GenerateTexture(const unsigned char * data, int channel, const Vec2i & siz);

	class CTextureAtlas {
	public:
		CTextureAtlas() = delete;
		CTextureAtlas(const char * filename, const std::unordered_map<std::string, std::pair<Vec2, Vec2>> & _uvs);
		virtual ~CTextureAtlas();

		bool GetUV(Vec2 * outLT, Vec2 * outRB, const char * uvKey) const {
			if(auto it = m_uvs.find(uvKey); it != m_uvs.end()) {
				* outLT = it->second.first;
				* outRB = it->second.second;
				return true;
			}
			return false;
		}

		unsigned int GetTextureId() const {
			return m_textureId;
		}

		const Vec2i & GetSize() const {
			return m_size;
		}

	private:
		unsigned int m_textureId = 0;
		Vec2i m_size {};
		std::unordered_map<std::string, std::pair<Vec2, Vec2>> m_uvs;
	};

	struct ISprite {

		virtual const Vec2i & GetSize() const = 0;
		virtual const Vec2 & GetOffset() const = 0;

		int GetWidth() const { return GetSize().x; }
		int GetHeight() const { return GetSize().y; }
		
		float GetXOffset() const { return GetOffset().x; }
		float GetYOffset() const { return GetOffset().y; }

		Vec2 GetTopLeftOffset() const {
			return { - GetXOffset(), - GetYOffset() };
		}
		Vec2 GetTopRightOffset() const {
			return { static_cast<float>(GetWidth()) - GetXOffset(), - GetYOffset() };
		}
		Vec2 GetBottomLeftOffset() const {
			return { - GetXOffset(), static_cast<float>(GetHeight()) - GetYOffset() };
		}
		Vec2 GetBottomRightOffset() const {
			return { static_cast<float>(GetWidth()) - GetXOffset(), static_cast<float>(GetHeight()) - GetYOffset() };
		}

		virtual void SetOffset(const Vec2 & vOffset) = 0;
		//virtual void SetSize(TODO) = 0; // TODO
	};

	struct SSpriteImage : public ISprite {
		SSpriteImage() = delete;
		// 会自动生成一个新的纹理页
		SSpriteImage(const unsigned char * data, int channel, Vec2i & refSize, Vec2 & refVOffset)
			: m_refSize { refSize }
			, m_refVOffset { refVOffset }
		{
			m_textureId = GenerateTexture(data, channel, refSize);
		}
		// 不会生成新的纹理页，直接使用现有纹理页
		SSpriteImage(unsigned int textureId, Vec2 uvLT, Vec2 uvRB, Vec2i & refSize, Vec2 & refVOffset)
			: m_textureId { textureId }
			, m_uvLT { uvLT }
			, m_uvRB { uvRB }
			, m_refSize { refSize }
			, m_refVOffset { refVOffset }
		{}
		virtual ~SSpriteImage();

		/* ---------- ISprite ---------- */
		virtual const Vec2i & GetSize() const override { return m_refSize; }
		virtual const Vec2 & GetOffset() const override { return m_refVOffset; }
	private:
		virtual void SetOffset(const Vec2 &) override {};
		/* ---------- ~ISprite ---------- */
	public:

		unsigned int GetTextureId() const {
			return m_textureId;
		}

		const Vec2 & GetUVLeftTop() const {
			return m_uvLT;
		}
		const Vec2 & GetUVRightBottom() const {
			return m_uvRB;
		}

		void SetUVLeftTop(const Vec2 & lt) {
			m_uvLT = lt;
		}
		void SetUVRightBottom(const Vec2 & rb) {
			m_uvRB = rb;
		}

	private:
		unsigned int m_textureId = 0;
		Vec2 m_uvLT { 0.f, 1.f };
		Vec2 m_uvRB { 1.f, 0.f };

		Vec2i & m_refSize;
		Vec2 & m_refVOffset;
	};

	class CStaticSprite : public ISprite {
	public:
		CStaticSprite() = delete;
		CStaticSprite(const char * filename);
		CStaticSprite(const CTextureAtlas * pTextureAtlas, const char * uvKey);
		virtual ~CStaticSprite();

		/* ---------- ISprite ---------- */
		virtual const Vec2i & GetSize() const override { return m_size; }
		virtual const Vec2 & GetOffset() const override { return m_vOffset; }

		virtual void SetOffset(const Vec2 & vOffset) override { m_vOffset = vOffset; }
		/* --------- ~ISprite ---------- */

		const SSpriteImage * GetImage() const { return m_pImage; }

	private:
		SSpriteImage * m_pImage;

		Vec2i m_size {};
		Vec2 m_vOffset {};
	};

	class CAnimatedSprite : public ISprite {
	public:
		CAnimatedSprite() = delete;
		CAnimatedSprite(const char * stripFilename, int frameCount);
		CAnimatedSprite(const CTextureAtlas * pTextureAtlas, std::initializer_list<const char *> uvKeys);
		// CAnimatedSprite(const char * gifFilename); // TODO

		virtual ~CAnimatedSprite();

		/* ---------- ISprite ---------- */
		virtual const Vec2i & GetSize() const override { return m_size; }
		virtual const Vec2 & GetOffset() const override { return m_vOffset; }

		virtual void SetOffset(const Vec2 & vOffset) override { m_vOffset = vOffset; }
		/* --------- ~ISprite ---------- */

		const SSpriteImage * GetFrame(int frame) const {
			return m_frames[frame % m_frameCount];
		}

		int GetFrameCount() const { return m_frameCount; }

	private:
		void ConstructErrorImages();

	private:
		SSpriteImage ** m_frames;
		int m_frameCount;

		Vec2i m_size {};
		Vec2 m_vOffset {};
	};

}
