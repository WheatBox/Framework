#pragma once

#include <FrameRender/RendererBase.h>

#include <FrameCore/BasicTypes.h>
#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

namespace Frame {

	class CRenderer;
	class CShader;

	class CShapeRenderer : public RendererBase::IColorAlpha {

	private:
		CRenderer * m_pRenderer;

		unsigned int m_VBO, m_VAO;

		struct SDefault {
			constexpr static float pixelSize = 1.f;
			constexpr static float lineWidth = 1.f;
			constexpr static float outlineWidth = 0.f;
		};

		CShader * const m_pDefaultShader;
		CShader * m_pShader = nullptr;

	public:

		CShapeRenderer(CRenderer * pRenderer);
		virtual ~CShapeRenderer();

		void ResetShader() { m_pShader = m_pDefaultShader; }
		void SetShader(CShader * pShader) { m_pShader = pShader; }
		CShader * GetShader() const { return m_pShader; }

		/* +-----------------------------------------------+ */
		/* |               Draw Basic Shapes               | */
		/* +-----------------------------------------------+ */

		void DrawBasicShapes(float * vertexBuffer, uint8 _GL_mode, int count);

		void DrawPoint(const Vec2 & vPos, float _size = SDefault::pixelSize) {
			DrawPointBlended(vPos, m_color, m_alpha, _size);
		}
		void DrawPointColorBlended(const Vec2 & vPos, const ColorRGB & rgb, float _size = SDefault::pixelSize) {
			DrawPointBlended(vPos, rgb, m_alpha, _size);
		}
		void DrawPointAlphaBlended(const Vec2 & vPos, float alpha, float _size = SDefault::pixelSize) {
			DrawPointBlended(vPos, m_color, alpha, _size);
		}
		void DrawPointBlended(Vec2 vPos, const ColorRGB & rgb, float alpha, float _size = SDefault::pixelSize);

		void DrawLine(const Vec2 & vPos1, const Vec2 & vPos2, float width = SDefault::lineWidth) {
			DrawLineBlended(vPos1, vPos2, m_color, m_alpha, width);
		}
		
		void DrawLineColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float width = SDefault::lineWidth) {
			DrawLineColorBlended(vPos1, vPos2, rgb, rgb, width);
		}
		void DrawLineColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb1, const ColorRGB & rgb2, float width = SDefault::lineWidth) {
			DrawLineBlended(vPos1, vPos2, rgb1, m_alpha, rgb2, m_alpha, width);
		}

		void DrawLineAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, float alpha, float width = SDefault::lineWidth) {
			DrawLineAlphaBlended(vPos1, vPos2, alpha, alpha, width);
		}
		void DrawLineAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, float alpha1, float alpha2, float width = SDefault::lineWidth) {
			DrawLineBlended(vPos1, vPos2, m_color, alpha1, m_color, alpha2, width);
		}
		
		void DrawLineBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float alpha, float width = SDefault::lineWidth) {
			DrawLineBlended(vPos1, vPos2, rgb, alpha, rgb, alpha, width);
		}
		void DrawLineBlended(Vec2 vPos1, Vec2 vPos2, const ColorRGB & rgb1, float alpha1, const ColorRGB & rgb2, float alpha2, float width = SDefault::lineWidth);

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangle(const Vec2 & vPos1, const Vec2 & vPos2, float outlineWidth = SDefault::outlineWidth) {
			DrawRectangleBlended(vPos1, vPos2, m_color, m_alpha, outlineWidth);
		}
		
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangleColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float outlineWidth = SDefault::outlineWidth) {
			DrawRectangleBlended(vPos1, vPos2, rgb, m_alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangleColorBlended(const Vec2 & vPos1, const Vec2 & vPos2,
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawRectangleBlended(vPos1, vPos2, rgbTL, m_alpha, rgbTR, m_alpha, rgbBL, m_alpha, rgbBR, m_alpha, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangleAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawRectangleBlended(vPos1, vPos2, m_color, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangleAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2,
			float alphaTL, float alphaTR, float alphaBL, float alphaBR,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawRectangleBlended(vPos1, vPos2, m_color, alphaTL, m_color, alphaTR, m_color, alphaBL, m_color, alphaBR, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangleBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawRectangleBlended(vPos1, vPos2, rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangleBlended(const Vec2 & vPosTL, const Vec2 & vPosBR,
			const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
			const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawQuadrilateralBlended(
				vPosTL, { vPosBR.x, vPosTL.y }, { vPosTL.x, vPosBR.y }, vPosBR,
				rgbTL, alphaTL, rgbTR, alphaTR,
				rgbBL, alphaBL, rgbBR, alphaBR,
				outlineWidth
			);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateral(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR, float outlineWidth = SDefault::outlineWidth) {
			DrawQuadrilateralBlended(vPosTL, vPosTR, vPosBL, vPosBR, m_color, m_alpha, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateralColorBlended(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR, const ColorRGB & rgb, float outlineWidth = SDefault::outlineWidth
		) {
			DrawQuadrilateralBlended(vPosTL, vPosTR, vPosBL, vPosBR, rgb, m_alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateralColorBlended(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR,
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawQuadrilateralBlended(vPosTL, vPosTR, vPosBL, vPosBR, rgbTL, m_alpha, rgbTR, m_alpha, rgbBL, m_alpha, rgbBR, m_alpha, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateralAlphaBlended(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawQuadrilateralBlended(vPosTL, vPosTR, vPosBL, vPosBR, m_color, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateralAlphaBlended(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR,
			float alphaTL,    float alphaTR,
			float alphaBL,    float alphaBR,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawQuadrilateralBlended(vPosTL, vPosTR, vPosBL, vPosBR, m_color, alphaTL, m_color, alphaTR, m_color, alphaBL, m_color, alphaBR, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateralBlended(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR, const ColorRGB & rgb, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawQuadrilateralBlended(vPosTL, vPosTR, vPosBL, vPosBR, rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateralBlended(Vec2 vPosTL, Vec2 vPosTR, Vec2 vPosBL, Vec2 vPosBR,
			const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
			const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
			float outlineWidth = SDefault::outlineWidth
		);

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangle(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3, float outlineWidth = SDefault::outlineWidth) {
			DrawTriangleBlended(vPos1, vPos2, vPos3, m_color, m_alpha, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangleColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3, const ColorRGB & rgb, float outlineWidth = SDefault::outlineWidth) {
			DrawTriangleBlended(vPos1, vPos2, vPos3, rgb, m_alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangleColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3,
			const ColorRGB & rgb1, const ColorRGB & rgb2, const ColorRGB & rgb3,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawTriangleBlended(vPos1, vPos2, vPos3, rgb1, m_alpha, rgb2, m_alpha, rgb3, m_alpha, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangleAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawTriangleBlended(vPos1, vPos2, vPos3, m_color, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangleAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3,
			float alpha1, float alpha2, float alpha3,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawTriangleBlended(vPos1, vPos2, vPos3, m_color, alpha1, m_color, alpha2, m_color, alpha3, outlineWidth);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangleBlended(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3, const ColorRGB & rgb, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawTriangleBlended(vPos1, vPos2, vPos3, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangleBlended(Vec2 vPos1, Vec2 vPos2, Vec2 vPos3,
			ColorRGB rgb1, float alpha1, ColorRGB rgb2, float alpha2, const ColorRGB & rgb3, float alpha3,
			float outlineWidth = SDefault::outlineWidth
		);

	};

}