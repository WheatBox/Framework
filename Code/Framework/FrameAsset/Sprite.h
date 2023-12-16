#pragma once

#include <FrameMath/Vector2.h>
#include <FrameMath/ColorMath.h>

namespace Frame {

	struct ISprite {

		ISprite(int & refWidth, int & refHeight, Vec2 & refVOffset)
			: m_refWidth { refWidth }
			, m_refHeight { refHeight }
			, m_refVOffset { refVOffset }
		{}

		int GetWidth() const { return m_refWidth; }
		int GetHeight() const { return m_refHeight; }

		const Vec2 & GetOffset() const { return m_refVOffset; }
		float GetXOffset() const { return m_refVOffset.x; }
		float GetYOffset() const { return m_refVOffset.y; }

		Vec2 GetTopLeftOffset() const {
			return { - m_refVOffset.x, - m_refVOffset.y };
		}
		Vec2 GetTopRightOffset() const {
			return { static_cast<float>(m_refWidth) - m_refVOffset.x, - m_refVOffset.y };
		}
		Vec2 GetBottomLeftOffset() const {
			return { - m_refVOffset.x, static_cast<float>(m_refHeight) - m_refVOffset.y };
		}
		Vec2 GetBottomRightOffset() const {
			return { static_cast<float>(m_refWidth) - m_refVOffset.x, static_cast<float>(m_refHeight) - m_refVOffset.y };
		}

		void SetOffset(const Vec2 & vOffset) { m_refVOffset = vOffset; }

	protected:
		int & m_refWidth;
		int & m_refHeight;
		Vec2 & m_refVOffset;

		unsigned int Generate(unsigned char * pData, int channel, int width, int height);
	};

	class CStaticSprite : public ISprite {
	public:
		CStaticSprite() = delete;

		CStaticSprite(const char * filename);
		CStaticSprite(unsigned int textureId, int & refWidth, int & refHeight, Vec2 & refVOffset)
			: ISprite { refWidth, refHeight, refVOffset }
			, m_textureId { textureId }
		{}

		// TODO - 若无法正常初始化，则将 m_textureId 设为一张错误提示图片

		virtual ~CStaticSprite();

		unsigned int GetTextureId() const { return m_textureId; }

	private:
		unsigned int m_textureId;

		int m_width = 0;
		int m_height = 0;
		Vec2 m_vOffset {};
	};

	class CAnimatedSprite : public ISprite {
	public:
		CAnimatedSprite() = delete;
		CAnimatedSprite(const char * stripFilename, int frameCount);
		// CAnimatedSprite(const char * gifFilename); // TODO

		// TODO - 若无法正常初始化，则将 m_textureId 设为一张错误提示图片
		virtual ~CAnimatedSprite();

		const CStaticSprite * GetFrame(int frame) const {
			return m_frames[frame % m_frameCount];
		}

		int GetFrameCount() const { return m_frameCount; }

	private:
		CStaticSprite ** m_frames;
		int m_frameCount;

		int m_width = 0;
		int m_height = 0;
		Vec2 m_vOffset {};
	};

}
