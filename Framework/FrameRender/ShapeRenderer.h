#pragma once

#include "../FrameMath/ColorMath.h"
#include "../FrameMath/Vector2.h"

namespace Frame {

	class CRenderer;
	class CShader;

	class CShapeRenderer final {

	private:
		CRenderer * m_pRenderer;

		unsigned int m_VBO, m_VAO;

		struct SDefault {
			constexpr static float pixelSize = 1.f;
			constexpr static float lineWidth = 1.f;
			constexpr static float outlineWidth = 0.f;
		};

		const CShader * m_pShader = nullptr;

	public:

		CShapeRenderer(CRenderer * pRenderer);

		void ResetShader();
		void SetShader(const CShader * pShader);
		const CShader * GetShader() const;

		/* +-----------------------------------------------+ */
		/* |               Draw Basic Shapes               | */
		/* +-----------------------------------------------+ */

		void DrawBasicShapes(float * vertexBuffer, uint8 _GL_mode, int count) const;

		void DrawPoint(Vec2 vPos, const ColorRGB & rgb, float alpha, float _size = SDefault::pixelSize) const;

		void DrawLine(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float alpha, float width = SDefault::lineWidth) const {
			DrawLine(vPos1, vPos2, rgb, alpha, rgb, alpha, width);
		}
		void DrawLine(Vec2 vPos1, Vec2 vPos2, const ColorRGB & rgb1, float alpha1, const ColorRGB & rgb2, float alpha2, float width = SDefault::lineWidth) const;

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangle(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float alpha, float outlineWidth = SDefault::outlineWidth) {
			DrawRectangle(vPos1, vPos2, rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawRectangle(const Vec2 & vPosTL, const Vec2 & vPosBR,
			const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
			const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
			float outlineWidth = SDefault::outlineWidth
		) {
			DrawQuadrilateral(
				vPosTL, { vPosBR.x, vPosTL.y }, { vPosTL.x, vPosBR.y }, vPosBR,
				rgbTL, alphaTL, rgbTR, alphaTR,
				rgbBL, alphaBL, rgbBR, alphaBR,
				outlineWidth
			);
		}

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateral(const Vec2 & vPosTL, const Vec2 & vPosTR, const Vec2 & vPosBL, const Vec2 & vPosBR, const ColorRGB & rgb, float alpha, float outlineWidth = SDefault::outlineWidth) const {
			DrawQuadrilateral(vPosTL, vPosTR, vPosBL, vPosBR, rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawQuadrilateral(Vec2 vPosTL, Vec2 vPosTR, Vec2 vPosBL, Vec2 vPosBR,
			const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
			const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
			float outlineWidth = SDefault::outlineWidth
		) const;

		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangle(const Vec2 & vPos1, const Vec2 & vPos2, const Vec2 & vPos3, const ColorRGB & rgb, float alpha, float outlineWidth = SDefault::outlineWidth) const {
			DrawTriangle(vPos1, vPos2, vPos3, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度，设为 0.0f 则是填充
		// outlineWidth : Outline width, set to 0.0f for filling
		void DrawTriangle(Vec2 vPos1, Vec2 vPos2, Vec2 vPos3,
			ColorRGB rgb1, float alpha1, ColorRGB rgb2, float alpha2, const ColorRGB & rgb3, float alpha3,
			float outlineWidth = SDefault::outlineWidth
		) const;

	};

}