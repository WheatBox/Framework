#pragma once

#include <FrameRender/IRenderer.h>

namespace Frame {

	class CShapeRenderer : public IRenderer {

	public:

		CShapeRenderer() = default;
		virtual ~CShapeRenderer() = default;

		/* +-----------------------------------------------+ */
		/* |               Draw Basic Shapes               | */
		/* +-----------------------------------------------+ */

		void DrawPixel(int x, int y);
		void DrawPixel(float x, float y);

		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawRectangle(int x1, int y1, int x2, int y2, bool fill = false);
		void DrawRectangle(float x1, float y1, float x2, float y2, bool fill = false);
		void DrawRectangleWH(int x, int y, int w, int h, bool fill = false);
		void DrawRectangleWH(float x, float y, float w, float h, bool fill = false);

	};

}