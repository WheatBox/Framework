#pragma once

#include <FrameRender/BasicRenderingTypes.h>

#include <FrameMath/Vector2.h>
#include <FrameMath/ColorMath.h>

namespace Frame {

	struct ISprite {

		virtual unsigned int GetTextureId() const = 0;

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		const Vec2 & GetOffset() const { return m_vOffset; }
		float GetXOffset() const { return m_vOffset.x; }
		float GetYOffset() const { return m_vOffset.y; }

		Vec2 GetTopLeftOffset() const {
			return { - m_vOffset.x, - m_vOffset.y };
		}
		Vec2 GetTopRightOffset() const {
			return { static_cast<float>(m_width) - m_vOffset.x, - m_vOffset.y };
		}
		Vec2 GetBottomLeftOffset() const {
			return { - m_vOffset.x, static_cast<float>(m_height) - m_vOffset.y };
		}
		Vec2 GetBottomRightOffset() const {
			return { static_cast<float>(m_width) - m_vOffset.x, static_cast<float>(m_height) - m_vOffset.y };
		}

		void SetOffset(const Vec2 & vOffset) { m_vOffset = vOffset; }

	protected:
		int m_width = 0;
		int m_height = 0;
		Vec2 m_vOffset {};
	};

	class CStaticSprite : public ISprite {
	public:
		CStaticSprite() = delete;

		CStaticSprite(const char * filename);

		// TODO - 若无法正常初始化，则将 sdlTexture 设为一张错误提示图片

		virtual ~CStaticSprite();

		virtual unsigned int GetTextureId() const override { return m_textureId; }

		void Generate(unsigned char * pData, int channel);

	private:
		unsigned int m_textureId = 0;
	};
}
