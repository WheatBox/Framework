#pragma once

#include <FrameCore/BasicTypes.h>
#include <FrameMath/Vector2.h>
#include <FrameMath/ColorMath.h>

namespace Frame {

	struct STextureVertexBuffer {

		static const uint8 s_dataLen = 4 * 9;

		float m_data[s_dataLen];

		virtual ~STextureVertexBuffer() = default;

		STextureVertexBuffer()
			: STextureVertexBuffer({ 0.f, 0.f }, { 0.f, 0.f }, 0xFFFFFF, 1.f)
		{}

		STextureVertexBuffer(
			float xTL, float yTL, float zTL, float rTL, float gTL, float bTL, float aTL,
			float xTR, float yTR, float zTR, float rTR, float gTR, float bTR, float aTR,
			float xBL, float yBL, float zBL, float rBL, float gBL, float bBL, float aBL,
			float xBR, float yBR, float zBR, float rBR, float gBR, float bBR, float aBR
		) : m_data {
		// Corresponding to the Shader:
		// 对应 Shader 中的：
		//      aPos                   aColor                 aTexCoord
		/* ---- 位置 ---- */     /* ---- 颜色 ---- */     /* -- 纹理坐标 -- */
		   xTL, yTL, zTL,        rTL, gTL, bTL, aTL,          0.f, 1.f,      // 左上 Top Left
		   xTR, yTR, zTR,        rTR, gTR, bTR, aTR,          1.f, 1.f,      // 右上 Top Right
		   xBL, yBL, zBL,        rBL, gBL, bBL, aBL,          0.f, 0.f,      // 左下 Bottom Left
		   xBR, yBR, zBR,        rBR, gBR, bBR, aBR,          1.f, 0.f       // 右下 Bottom Right
		           // ^
		           // |      也许哪天用得上
		           // +----- Maybe one day I'll need them
		} {}

		STextureVertexBuffer(
			const Vec2 & vPosTL, const ColorRGB & rgbTL, float aTL,    const Vec2 & vPosTR, const ColorRGB & rgbTR, float aTR,
			const Vec2 & vPosBL, const ColorRGB & rgbBL, float aBL,    const Vec2 & vPosBR, const ColorRGB & rgbBR, float aBR
		) : STextureVertexBuffer(
			vPosTL.x, vPosTL.y, 0.f, ONERGB(rgbTL), aTL,
			vPosTR.x, vPosTR.y, 0.f, ONERGB(rgbTR), aTR,
			vPosBL.x, vPosBL.y, 0.f, ONERGB(rgbBL), aBL,
			vPosBR.x, vPosBR.y, 0.f, ONERGB(rgbBR), aBR
		) {}

		STextureVertexBuffer(
			const Vec2 & vPosTL,    const Vec2 & vPosTR,
			const Vec2 & vPosBL,    const Vec2 & vPosBR,
			const ColorRGB & rgb, float alpha
		) : STextureVertexBuffer(
			vPosTL.x, vPosTL.y, 0.f, ONERGB(rgb), alpha,
			vPosTR.x, vPosTR.y, 0.f, ONERGB(rgb), alpha,
			vPosBL.x, vPosBL.y, 0.f, ONERGB(rgb), alpha,
			vPosBR.x, vPosBR.y, 0.f, ONERGB(rgb), alpha
		) {}

		STextureVertexBuffer(
			const Vec2 & vPosTL, const Vec2 & vPosBR,
			const ColorRGB & rgb, float alpha
		) : STextureVertexBuffer(
			vPosTL.x, vPosTL.y, 0.f, ONERGB(rgb), alpha,
			vPosBR.x, vPosTL.y, 0.f, ONERGB(rgb), alpha,
			vPosTL.x, vPosBR.y, 0.f, ONERGB(rgb), alpha,
			vPosBR.x, vPosBR.y, 0.f, ONERGB(rgb), alpha
		) {}

		STextureVertexBuffer(
			const Vec2 & vPosTL, const Vec2 & vPosBR,
			const ColorRGB & rgbTL, float aTL,    const ColorRGB & rgbTR, float aTR,
			const ColorRGB & rgbBL, float aBL,    const ColorRGB & rgbBR, float aBR
		) : STextureVertexBuffer(
			vPosTL.x, vPosTL.y, 0.f, ONERGB(rgbTL), aTL,
			vPosBR.x, vPosTL.y, 0.f, ONERGB(rgbTR), aTR,
			vPosTL.x, vPosBR.y, 0.f, ONERGB(rgbBL), aBL,
			vPosBR.x, vPosBR.y, 0.f, ONERGB(rgbBR), aBR
		) {}

		void SetPositions(const Vec2 & vPosTL, const Vec2 & vPosBR) {
			SetPositions(
				vPosTL.x, vPosTL.y,
				vPosBR.x, vPosTL.y,
				vPosTL.x, vPosBR.y,
				vPosBR.x, vPosBR.y
			);
		}
		void SetPositions(
			const Vec2 & vPosTL,    const Vec2 & vPosTR,
			const Vec2 & vPosBL,    const Vec2 & vPosBR
		) {
			SetPositions(
				vPosTL.x, vPosTL.y,
				vPosTR.x, vPosTR.y,
				vPosBL.x, vPosBL.y,
				vPosBR.x, vPosBR.y
			);
		}
		void SetPositions(
			float xTL, float yTL,    float xTR, float yTR,
			float xBL, float yBL,    float xBR, float yBR
		) {
			m_data[0]  = xTL; m_data[1]  = yTL;
			m_data[9]  = xTR; m_data[10] = yTR;
			m_data[18] = xBL; m_data[19] = yBL;
			m_data[27] = xBR; m_data[28] = yBR;
		}

		void SetBlends(const ColorRGB & rgb, float alpha) {
			SetBlends(
				ONERGB(rgb), alpha,
				ONERGB(rgb), alpha,
				ONERGB(rgb), alpha,
				ONERGB(rgb), alpha
			);
		}
		void SetBlends(
			const ColorRGB & rgbTL, float aTL,    const ColorRGB & rgbTR, float aTR,
			const ColorRGB & rgbBL, float aBL,    const ColorRGB & rgbBR, float aBR
		) {
			SetBlends(
				ONERGB(rgbTL), aTL,
				ONERGB(rgbTR), aTR,
				ONERGB(rgbBL), aBL,
				ONERGB(rgbBR), aBR
			);
		}
		void SetBlends(
			float rTL, float gTL, float bTL, float aTL,    float rTR, float gTR, float bTR, float aTR,
			float rBL, float gBL, float bBL, float aBL,    float rBR, float gBR, float bBR, float aBR
		) {
			SetColorBlends(
				rTL, gTL, bTL,
				rTR, gTR, bTR,
				rBL, gBL, bBL,
				rBR, gBR, bBR
			);
			SetAlphaBlends(aTL, aTR, aBL, aBR);
		}

		void SetColorBlends(const ColorRGB & rgb) {
			SetColorBlends(rgb, rgb, rgb, rgb);
		}
		void SetColorBlends(
			const ColorRGB & rgbTL,    const ColorRGB & rgbTR,
			const ColorRGB & rgbBL,    const ColorRGB & rgbBR
		) {
			SetColorBlends(ONERGB(rgbTL), ONERGB(rgbTR), ONERGB(rgbBL), ONERGB(rgbBR));
		}
		void SetColorBlends(
			float rTL, float gTL, float bTL,    float rTR, float gTR, float bTR,
			float rBL, float gBL, float bBL,    float rBR, float gBR, float bBR
		) {
			m_data[3]  = rTL; m_data[4]  = gTL; m_data[5]  = bTL;
			m_data[12] = rTR; m_data[13] = gTR; m_data[14] = bTR;
			m_data[21] = rBL; m_data[22] = gBL; m_data[23] = bBL;
			m_data[30] = rBR; m_data[31] = gBR; m_data[32] = bBR;
		}

		void SetAlphaBlends(float alpha) {
			SetAlphaBlends(alpha, alpha, alpha, alpha);
		}
		void SetAlphaBlends(float aTL, float aTR, float aBL, float aBR) {
			m_data[6]  = aTL; m_data[15] = aTR; m_data[24] = aBL; m_data[33] = aBR;
		}

		void SetTexCoord(const Vec2 & uvLT, const Vec2 & uvRB) { // 0 1   1 0
			m_data[7]  = uvLT.x; m_data[8]  = uvLT.y; // Top Left
			m_data[16] = uvRB.x; m_data[17] = uvLT.y; // Top Right
			m_data[25] = uvLT.x; m_data[26] = uvRB.y; // Bottom Left
			m_data[34] = uvRB.x; m_data[35] = uvRB.y; // Bottom Right
		}
	};

}