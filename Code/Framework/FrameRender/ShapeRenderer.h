#pragma once

#include <FrameCore/BasicTypes.h>
#include <FrameMath/ColorMath.h>
#include <FrameMath/Vector2.h>

namespace Frame {

	class CRenderer;

	class CShapeRenderer {

	private:
		CRenderer * m_pRenderer;

		unsigned int m_VBO, m_VAO;

		const ColorRGB & m_color;
		const float & m_alpha;

	public:

		constexpr static float s_defaultSize = 1.f;

		CShapeRenderer(CRenderer * pRenderer);
		virtual ~CShapeRenderer() = default;

		/* +-----------------------------------------------+ */
		/* |               Draw Basic Shapes               | */
		/* +-----------------------------------------------+ */

		void DrawBasicShapes(float * vertexBuffer, uint8 _GL_mode, int count);

		void DrawPixel(const Vec2 & vPos, float _size = s_defaultSize) {
			DrawPixelBlended(vPos, m_color, m_alpha, _size);
		}
		void DrawPixelColorBlended(const Vec2 & vPos, const ColorRGB & rgb, float _size = s_defaultSize) {
			DrawPixelBlended(vPos, rgb, m_alpha, _size);
		}
		void DrawPixelAlphaBlended(const Vec2 & vPos, float alpha, float _size = s_defaultSize) {
			DrawPixelBlended(vPos, m_color, alpha, _size);
		}
		void DrawPixelBlended(Vec2 vPos, const ColorRGB & rgb, float alpha, float _size = s_defaultSize);

		void DrawLine(const Vec2 & vPos1, const Vec2 & vPos2, float width = s_defaultSize) {
			DrawLineBlended(vPos1, vPos2, m_color, m_alpha, width);
		}
		
		void DrawLineColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float width = s_defaultSize) {
			DrawLineColorBlended(vPos1, vPos2, rgb, rgb, width);
		}
		void DrawLineColorBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb1, const ColorRGB & rgb2, float width = s_defaultSize) {
			DrawLineBlended(vPos1, vPos2, rgb1, m_alpha, rgb2, m_alpha, width);
		}

		void DrawLineAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, float alpha, float width = s_defaultSize) {
			DrawLineAlphaBlended(vPos1, vPos2, alpha, alpha, width);
		}
		void DrawLineAlphaBlended(const Vec2 & vPos1, const Vec2 & vPos2, float alpha1, float alpha2, float width = s_defaultSize) {
			DrawLineBlended(vPos1, vPos2, m_color, alpha1, m_color, alpha2, width);
		}
		
		void DrawLineBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float alpha, float width = s_defaultSize) {
			DrawLineBlended(vPos1, vPos2, rgb, alpha, rgb, alpha, width);
		}
		void DrawLineBlended(Vec2 vPos1, Vec2 vPos2, const ColorRGB & rgb1, float alpha1, const ColorRGB & rgb2, float alpha2, float width = s_defaultSize);

		// outlineWidth : 轮廓线宽度（默认 1.0f），设为 0.0f 则是填充
		// outlineWidth : Outline width (default 1.0f), set to 0.0f for filling
		void DrawRectangle(const Vec2 & vPos1, const Vec2 & vPos2, float outlineWidth = s_defaultSize) {
			DrawRectangleBlended(vPos1, vPos2, m_color, m_alpha, outlineWidth);
		}
		
		// TODO - DrawRectangleColorBlended...
		//        DrawRectangleAlphaBlended...

		// outlineWidth : 轮廓线宽度（默认 1.0f），设为 0.0f 则是填充
		// outlineWidth : Outline width (default 1.0f), set to 0.0f for filling
		void DrawRectangleBlended(const Vec2 & vPos1, const Vec2 & vPos2, const ColorRGB & rgb, float alpha, float outlineWidth = s_defaultSize) {
			DrawRectangleBlended(vPos1, vPos2, rgb, alpha, rgb, alpha, rgb, alpha, rgb, alpha, outlineWidth);
		}
		// outlineWidth : 轮廓线宽度（默认 1.0f），设为 0.0f 则是填充
		// outlineWidth : Outline width (default 1.0f), set to 0.0f for filling
		void DrawRectangleBlended(const Vec2 & vPosTL, const Vec2 & vPosBR,
			const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
			const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
			float outlineWidth = s_defaultSize
		) {
			DrawQuadrilateralBlended(
				vPosTL, { vPosBR.x, vPosTL.y }, { vPosTL.x, vPosBR.y }, vPosBR,
				rgbTL, alphaTL, rgbTR, alphaTR,
				rgbBL, alphaBL, rgbBR, alphaBR,
				outlineWidth
			);
		}

		// TODO - DrawQuadrilateral...

		// outlineWidth : 轮廓线宽度（默认 1.0f），设为 0.0f 则是填充
		// outlineWidth : Outline width (default 1.0f), set to 0.0f for filling
		void DrawQuadrilateralBlended(Vec2 vPosTL, Vec2 vPosTR, Vec2 vPosBL, Vec2 vPosBR,
			const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
			const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
			float outlineWidth = s_defaultSize
		);

		void DrawRectangleWH(float x, float y, float w, float h, bool fill = false);

	};

}