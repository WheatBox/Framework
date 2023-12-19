#pragma once

#include <FrameMath/Vector2.h>
#include <FrameMath/ColorMath.h>

namespace Frame {

	struct ISprite {

		virtual std::pair<int, int> GetSize() const = 0;
		virtual Vec2 GetOffset() const = 0;

		int GetWidth() const { return GetSize().first; }
		int GetHeight() const { return GetSize().second; }
		
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
		SSpriteImage(const unsigned char * data, int channel, int & refWidth, int & refHeight, Vec2 & refVOffset);
		virtual ~SSpriteImage();

		/* ---------- ISprite ---------- */
		virtual std::pair<int, int> GetSize() const override { return { m_refWidth, m_refHeight }; }
		virtual Vec2 GetOffset() const override { return m_refVOffset; }
	private:
		virtual void SetOffset(const Vec2 &) override {};
		/* ---------- ~ISprite ---------- */
	public:

		unsigned int GetTextureId() const {
			return m_textureId;
		}

	private:
		unsigned int m_textureId = 0;

		int & m_refWidth;
		int & m_refHeight;
		Vec2 & m_refVOffset;

		unsigned int Generate(const unsigned char * data, int channel, int width, int height);
	};

	class CStaticSprite : public ISprite {
	public:
		CStaticSprite() = delete;
		CStaticSprite(const char * filename);
		virtual ~CStaticSprite();

		/* ---------- ISprite ---------- */
		virtual std::pair<int, int> GetSize() const override { return { m_width, m_height }; }
		virtual Vec2 GetOffset() const override { return m_vOffset; }

		virtual void SetOffset(const Vec2 & vOffset) override { m_vOffset = vOffset; }
		/* --------- ~ISprite ---------- */

		const SSpriteImage * GetImage() const { return m_pImage; }

	private:
		SSpriteImage * m_pImage;

		int m_width = 0;
		int m_height = 0;
		Vec2 m_vOffset {};
	};

	class CAnimatedSprite : public ISprite {
	public:
		CAnimatedSprite() = delete;
		CAnimatedSprite(const char * stripFilename, int frameCount);
		// CAnimatedSprite(const char * gifFilename); // TODO

		virtual ~CAnimatedSprite();

		/* ---------- ISprite ---------- */
		virtual std::pair<int, int> GetSize() const override { return { m_width, m_height }; }
		virtual Vec2 GetOffset() const override { return m_vOffset; }

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

		int m_width = 0;
		int m_height = 0;
		Vec2 m_vOffset {};
	};

}
