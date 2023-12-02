#pragma once

#include <FrameRender/BasicRenderingTypes.h>

#include <FrameRender/TextureVertexBuffer.h>
#include <FrameRender/ShapeRenderer.h>
#include <FrameRender/TextRenderer.h>
#include <FrameRender/Shader.h>

#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

struct GLFWwindow;

namespace Frame {

	class CRenderer {

	public:

		CRenderer();
		virtual ~CRenderer();

		void Initialize(int windowWidth, int windowHeight);

		void FramebufferResizeCallback(int width, int height);

		CShapeRenderer * pShapeRenderer = nullptr;
		CTextRenderer * pTextRenderer = nullptr;

	private:
		int m_windowWidth = 0, m_windowHeight = 0;

		// 顶点缓冲对象(Vertex Buffer Object, VBO)
		// 顶点数组对象(Vertex Array Object, VAO)
		// 元素缓冲对象(Element Buffer Object，EBO)，or 索引缓冲对象(Index Buffer Object，IBO)
		unsigned int m_VBO = 0, m_VAO = 0, m_EBO = 0;

		STextureVertexBuffer m_defaultTextureVertexBuffer {};

		ColorRGB m_backgroundColor { 0, 0, 0 };

		ColorRGB m_color { 255, 255, 255 };
		float m_alpha = 1.f;

		CShader * const m_pDefaultShader;
		CShader * m_pShader = nullptr;

	public:
		void RenderBegin();
		void RenderEnd();

		void ResetShader() { m_pShader = m_pDefaultShader; }
		void SetShader(CShader * pShader) { m_pShader = pShader; }
		CShader * GetShader() const { return m_pShader; }

		Vec2 Project(const Vec2 & pos) const {
			return {
				pos.x * 2.f / m_windowWidth - 1.f,
				-pos.y * 2.f / m_windowHeight + 1.f,
			};
		}

		void Project(Vec2 * pos) const {
			pos->x = pos->x * 2.f / m_windowWidth - 1.f;
			pos->y = -pos->y * 2.f / m_windowHeight + 1.f;
		}

		void Project(float * _x, float * _y) const {
			* _x = (* _x) * 2.f / m_windowWidth - 1.f;
			* _y = -(* _y) * 2.f / m_windowHeight + 1.f;
		}

		STextureVertexBuffer & GetTextureVertexBuffer() {
			return m_defaultTextureVertexBuffer;
		}

		/* +-----------------------------------------------+ */
		/* |                Set Draw Params                | */
		/* +-----------------------------------------------+ */

		void SetColor(const ColorRGB & rgb) {
			m_color = rgb;
			m_defaultTextureVertexBuffer.SetColorBlends(m_color);
		}
		void SetColor(uint8 r, uint8 g, uint8 b) {
			SetColor({ r, g, b });
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
		void SetColorAlpha(uint8 r, uint8 g, uint8 b, float alpha) {
			SetColorAlpha({ r, g, b }, alpha);
		}

		const ColorRGB & GetColor() const { return m_color; }
		const float & GetAlpha() const { return m_alpha; }
		//          ^
		//      此处的引用是为了给其它子渲染器成员变量使用，例如 pShapeRenderer（参见 CShapeRenderer::m_alpha）
		//      The reference here is intended for use by other sub renderer member variables such as pShapeRenderer (see also CShapeRenderer::m_alpha)

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
		void DrawTexture(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer, const CShader * _pShader);

		void DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, STextureVertexBuffer & textureVertexBuffer);
		void DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, const Vec2 & vScale, float angle, STextureVertexBuffer & textureVertexBuffer);
		void DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, STextureVertexBuffer && textureVertexBuffer) {
			DrawSprite(pSprite, vPos, static_cast<STextureVertexBuffer &>(textureVertexBuffer));
		}
		void DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, const Vec2 & vScale, float angle, STextureVertexBuffer && textureVertexBuffer) {
			DrawSprite(pSprite, vPos, vScale, angle, static_cast<STextureVertexBuffer &>(textureVertexBuffer));
		}

		void DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos) {
			DrawSprite(pSprite, vPos, m_defaultTextureVertexBuffer);
		}
		void DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, const Vec2 & vScale, float angle) {
			DrawSprite(pSprite, vPos, vScale, angle, m_defaultTextureVertexBuffer);
		}

		void DrawSpriteColorBlended(CStaticSprite * pSprite, const Vec2 & vPos, const ColorRGB & rgb) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgb);
			DrawSprite(pSprite, vPos, textureVertexBuffer);
		}
		void DrawSpriteColorBlended(CStaticSprite * pSprite, const Vec2 & vPos, const ColorRGB & rgb, const Vec2 & vScale, float angle) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgb);
			DrawSprite(pSprite, vPos, vScale, angle, textureVertexBuffer);
		}
		void DrawSpriteColorBlended(CStaticSprite * pSprite, const Vec2 & vPos,
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgbTL, rgbTR, rgbBL, rgbBR);
			DrawSprite(pSprite, vPos, textureVertexBuffer);
		}
		void DrawSpriteColorBlended(CStaticSprite * pSprite, const Vec2 & vPos,
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR,
			const Vec2 & vScale, float angle
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetColorBlends(rgbTL, rgbTR, rgbBL, rgbBR);
			DrawSprite(pSprite, vPos, vScale, angle, textureVertexBuffer);
		}
		
		void DrawSpriteAlphaBlended(CStaticSprite * pSprite, const Vec2 & vPos, float alpha) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(alpha);
			DrawSprite(pSprite, vPos, textureVertexBuffer);
		}
		void DrawSpriteAlphaBlended(CStaticSprite * pSprite, const Vec2 & vPos, float alpha, const Vec2 & vScale, float angle) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(alpha);
			DrawSprite(pSprite, vPos, vScale, angle, textureVertexBuffer);
		}
		void DrawSpriteAlphaBlended(CStaticSprite * pSprite, const Vec2 & vPos,
			float aTL,    float aTR,
			float aBL,    float aBR
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(aTL, aTR, aBL, aBR);
			DrawSprite(pSprite, vPos, textureVertexBuffer);
		}
		void DrawSpriteAlphaBlended(CStaticSprite * pSprite, const Vec2 & vPos,
			float aTL,    float aTR,
			float aBL,    float aBR,
			const Vec2 & vScale, float angle
		) {
			STextureVertexBuffer textureVertexBuffer = m_defaultTextureVertexBuffer;
			textureVertexBuffer.SetAlphaBlends(aTL, aTR, aBL, aBR);
			DrawSprite(pSprite, vPos, vScale, angle, textureVertexBuffer);
		}
		
		void DrawSpriteBlended(CStaticSprite * pSprite, const Vec2 & vPos, const ColorRGB & rgb, float alpha) {
			DrawSprite(pSprite, vPos, { {}, {},
				rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha
			});
		}
		void DrawSpriteBlended(CStaticSprite * pSprite, const Vec2 & vPos, const ColorRGB & rgb, float alpha, const Vec2 & vScale, float angle) {
			DrawSprite(pSprite, vPos, vScale, angle, { {}, {},
				rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha
			});
		}
		void DrawSpriteBlended(CStaticSprite * pSprite, const Vec2 & vPos,
			const ColorRGB & rgbTL, float aTL,    const ColorRGB & rgbTR, float aTR,
			const ColorRGB & rgbBL, float aBL,    const ColorRGB & rgbBR, float aBR
		) {;
			DrawSprite(pSprite, vPos, { {}, {},
				rgbTL, aTL, rgbTR, aTR, rgbBL, aBL, rgbBR, aBR
			});
		}
		void DrawSpriteBlended(CStaticSprite * pSprite, const Vec2 & vPos,
			const ColorRGB & rgbTL, float aTL,    const ColorRGB & rgbTR, float aTR,
			const ColorRGB & rgbBL, float aBL,    const ColorRGB & rgbBR, float aBR,
			const Vec2 & vScale, float angle
		) {
			DrawSprite(pSprite, vPos, vScale, angle, { {}, {},
				rgbTL, aTL, rgbTR, aTR, rgbBL, aBL, rgbBR, aBR
			});
		}

	};

}