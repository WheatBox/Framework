#pragma once

#include <FrameRender/RendererBase.h>

#include <FrameRender/TextureVertexBuffer.h>
#include <FrameRender/ShapeRenderer.h>
#include <FrameRender/TextRenderer.h>
#include <FrameRender/Shader.h>

#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

struct GLFWwindow;

namespace Frame {

	struct SSpriteImage;

	class CRenderer : public RendererBase::IColorAlpha {

	public:
		/* +------- RendererBaseClass::IColorAlpha --------+ */

		void SetColor(const ColorRGB & rgb) {
			m_color = rgb;
			m_defaultTextureVertexBuffer.SetColorBlends(m_color);
		}
		void SetAlpha(float alpha) {
			m_alpha = alpha;
			m_defaultTextureVertexBuffer.SetAlphaBlends(alpha);
		}
		void SetColorAlpha(const ColorRGB & rgb, float alpha) {
			m_color = rgb;
			m_alpha = alpha;
			m_defaultTextureVertexBuffer.SetBlends(m_color, alpha);
		}

		/* +------ ~RendererBaseClass::IColorAlpha --------+ */

	public:

		CRenderer();
		virtual ~CRenderer();

		void Initialize();

		CShapeRenderer * pShapeRenderer = nullptr;
		CTextRenderer * pTextRenderer = nullptr;

		static inline unsigned int s_currentVAO = 0;
		static inline unsigned int s_currentVBO = 0;
		static inline unsigned int s_currentTextureId = 0;

	private:

		// 顶点缓冲对象(Vertex Buffer Object, VBO)
		// 顶点数组对象(Vertex Array Object, VAO)
		// 元素缓冲对象(Element Buffer Object，EBO)，or 索引缓冲对象(Index Buffer Object，IBO)
		unsigned int m_VBO = 0, m_VAO = 0, m_EBO = 0;

		STextureVertexBuffer m_defaultTextureVertexBuffer {};

		ColorRGB m_backgroundColor { 0, 0, 0 };

		CShader * const m_pDefaultShader;
		CShader * m_pShader = nullptr;

	public:
		void RenderBegin();
		void RenderEnd();

		void ResetShader() { m_pShader = m_pDefaultShader; }
		void SetShader(CShader * pShader) { m_pShader = pShader; }
		CShader * GetShader() const { return m_pShader; }

		void SetShaderProjectionUniforms(CShader * pShader) const;

		STextureVertexBuffer & GetTextureVertexBuffer() {
			return m_defaultTextureVertexBuffer;
		}

		void Clear(ColorRGB color, float alpha);

		/* +-----------------------------------------------+ */
		/* |                Set Draw Params                | */
		/* +-----------------------------------------------+ */

		void SetBackgroundColor(const ColorRGB & rgb) {
			m_backgroundColor = rgb;
		}
		void SetBackgroundColor(uint8 r, uint8 g, uint8 b) {
			m_backgroundColor.Set(r, g, b);
		}

		const ColorRGB & GetBackgroundColor() const { return m_backgroundColor; }

		/* +-----------------------------------------------+ */
		/* |                  Draw Sprite                  | */
		/* +-----------------------------------------------+ */

		void DrawTexture(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer) {
			DrawTexture(textureId, textureVertexBuffer, m_pShader);
		}
		void DrawTexture(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer, CShader * _pShader);
		
		void DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, STextureVertexBuffer & textureVertexBuffer);
		void DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const Vec2 & vScale, float angle, STextureVertexBuffer & textureVertexBuffer);
		void DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, STextureVertexBuffer && textureVertexBuffer) {
			DrawSprite(pSpriteImage, vPos, static_cast<STextureVertexBuffer &>(textureVertexBuffer));
		}
		void DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const Vec2 & vScale, float angle, STextureVertexBuffer && textureVertexBuffer) {
			DrawSprite(pSpriteImage, vPos, vScale, angle, static_cast<STextureVertexBuffer &>(textureVertexBuffer));
		}

		void DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos) {
			DrawSprite(pSpriteImage, vPos, m_defaultTextureVertexBuffer);
		}
		void DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const Vec2 & vScale, float angle) {
			DrawSprite(pSpriteImage, vPos, vScale, angle, m_defaultTextureVertexBuffer);
		}

		void DrawSpriteColorBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const ColorRGB & rgb) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgb);
			DrawSprite(pSpriteImage, vPos, textureVertexBuffer);
		}
		void DrawSpriteColorBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const ColorRGB & rgb, const Vec2 & vScale, float angle) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgb);
			DrawSprite(pSpriteImage, vPos, vScale, angle, textureVertexBuffer);
		}
		void DrawSpriteColorBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos,
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgbTL, rgbTR, rgbBL, rgbBR);
			DrawSprite(pSpriteImage, vPos, textureVertexBuffer);
		}
		void DrawSpriteColorBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos,
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR,
			const Vec2 & vScale, float angle
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgbTL, rgbTR, rgbBL, rgbBR);
			DrawSprite(pSpriteImage, vPos, vScale, angle, textureVertexBuffer);
		}
		
		void DrawSpriteAlphaBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos, float alpha) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(alpha);
			DrawSprite(pSpriteImage, vPos, textureVertexBuffer);
		}
		void DrawSpriteAlphaBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos, float alpha, const Vec2 & vScale, float angle) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(alpha);
			DrawSprite(pSpriteImage, vPos, vScale, angle, textureVertexBuffer);
		}
		void DrawSpriteAlphaBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos,
			float aTL,    float aTR,
			float aBL,    float aBR
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(aTL, aTR, aBL, aBR);
			DrawSprite(pSpriteImage, vPos, textureVertexBuffer);
		}
		void DrawSpriteAlphaBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos,
			float aTL,    float aTR,
			float aBL,    float aBR,
			const Vec2 & vScale, float angle
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(aTL, aTR, aBL, aBR);
			DrawSprite(pSpriteImage, vPos, vScale, angle, textureVertexBuffer);
		}
		
		void DrawSpriteBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			DrawSprite(pSpriteImage, vPos, { {}, {},
				rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha
			});
		}
		void DrawSpriteBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const ColorRGB & rgb, float alpha, const Vec2 & vScale, float angle) {
			DrawSprite(pSpriteImage, vPos, vScale, angle, { {}, {},
				rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha
			});
		}
		void DrawSpriteBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos,
			const ColorRGB & rgbTL, float aTL,    const ColorRGB & rgbTR, float aTR,
			const ColorRGB & rgbBL, float aBL,    const ColorRGB & rgbBR, float aBR
		) {;
			DrawSprite(pSpriteImage, vPos, { {}, {},
				rgbTL, aTL, rgbTR, aTR, rgbBL, aBL, rgbBR, aBR
			});
		}
		void DrawSpriteBlended(const SSpriteImage * pSpriteImage, const Vec2 & vPos,
			const ColorRGB & rgbTL, float aTL,    const ColorRGB & rgbTR, float aTR,
			const ColorRGB & rgbBL, float aBL,    const ColorRGB & rgbBR, float aBR,
			const Vec2 & vScale, float angle
		) {
			DrawSprite(pSpriteImage, vPos, vScale, angle, { {}, {},
				rgbTL, aTL, rgbTR, aTR, rgbBL, aBL, rgbBR, aBR
			});
		}

	};

}