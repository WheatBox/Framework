#pragma once

#include <FrameMath/Vector2.h>

namespace Frame {

	class CRenderer;

	class CShapeRenderer {

	private:
		CRenderer * m_pRenderer;

	public:

		CShapeRenderer(CRenderer * pRenderer)
			: m_pRenderer { pRenderer }
		{}
		virtual ~CShapeRenderer() = default;

		/* +-----------------------------------------------+ */
		/* |               Draw Basic Shapes               | */
		/* +-----------------------------------------------+ */

		void DrawPixel(const Vec2 & vPos) {
			DrawPixel(vPos.x, vPos.y);
		}
		void DrawPixel(float x, float y);

		void DrawLine(const Vec2 & vPos1, const Vec2 & vPos2) {
			DrawLine(vPos1.x, vPos1.y, vPos2.x, vPos2.y);
		}
		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawRectangle(float x1, float y1, float x2, float y2, bool fill = false);
		void DrawRectangleWH(float x, float y, float w, float h, bool fill = false);

	};

}