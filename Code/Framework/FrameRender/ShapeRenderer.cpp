#include <FrameRender/ShapeRenderer.h>

#include <FrameRender/Renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	CShapeRenderer::CShapeRenderer(CRenderer * pRenderer)
		: m_pRenderer { pRenderer }
		, m_color { pRenderer->GetColor() }
		, m_alpha { pRenderer->GetAlpha() }
	{
		glGenBuffers(1, & m_VBO);
		glGenVertexArrays(1, & m_VAO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		GLsizei stride = (3 + 4) * (GLsizei)sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	/* +-----------------------------------------------+ */
	/* |               Draw Basic Shapes               | */
	/* +-----------------------------------------------+ */

	void CShapeRenderer::DrawBasicShapes(float * vertexBuffer, uint8 _GL_mode, int count) {
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * static_cast<size_t>(count * 7), vertexBuffer, GL_DYNAMIC_DRAW);
		m_pRenderer->pSolidColorShader->Use();
		glDrawArrays(_GL_mode, 0, count);
	}

	void CShapeRenderer::DrawPixelBlended(Vec2 vPos, const ColorRGB & rgb, float alpha, float _size) {
		m_pRenderer->Project(& vPos);
		float vertexBuffer[] = { vPos.x, vPos.y, 0.f, ONERGB(rgb), alpha };
		glPointSize(_size);
		DrawBasicShapes(vertexBuffer, GL_POINTS, 1);
	}

	void CShapeRenderer::DrawLineBlended(Vec2 vPos1, Vec2 vPos2, const ColorRGB & rgb1, float alpha1, const ColorRGB & rgb2, float alpha2, float width) {
		m_pRenderer->Project(& vPos1);
		m_pRenderer->Project(& vPos2);
		float vertexBuffer[] = {
			vPos1.x, vPos1.y, 0.f, ONERGB(rgb1), alpha1,
			vPos2.x, vPos2.y, 0.f, ONERGB(rgb2), alpha2
		};
		glLineWidth(width);
		DrawBasicShapes(vertexBuffer, GL_LINES, 2);
	}

	void CShapeRenderer::DrawQuadrilateralBlended(Vec2 vPosTL, Vec2 vPosTR, Vec2 vPosBL, Vec2 vPosBR,
		const ColorRGB & rgbTL, float alphaTL,    const ColorRGB & rgbTR, float alphaTR,
		const ColorRGB & rgbBL, float alphaBL,    const ColorRGB & rgbBR, float alphaBR,
		float outlineWidth
	) {
		m_pRenderer->Project(& vPosTL);
		m_pRenderer->Project(& vPosTR);
		m_pRenderer->Project(& vPosBL);
		m_pRenderer->Project(& vPosBR);
		if(outlineWidth) {
			glLineWidth(outlineWidth);
			float vertexBuffer[] = {
				vPosTL.x, vPosTL.y, 0.f, ONERGB(rgbTL), alphaTL,
				vPosTR.x, vPosTR.y, 0.f, ONERGB(rgbTR), alphaTR,
				vPosBR.x, vPosBR.y, 0.f, ONERGB(rgbBR), alphaBR,
				vPosBL.x, vPosBL.y, 0.f, ONERGB(rgbBL), alphaBL
			};
			DrawBasicShapes(vertexBuffer, GL_LINE_LOOP, 4);
		} else {
			float vertexBuffer[] = {
				vPosTR.x, vPosTR.y, 0.f, ONERGB(rgbTR), alphaTR,
				vPosTL.x, vPosTL.y, 0.f, ONERGB(rgbTL), alphaTL,
				vPosBR.x, vPosBR.y, 0.f, ONERGB(rgbBR), alphaBR,
				vPosBL.x, vPosBL.y, 0.f, ONERGB(rgbBL), alphaBL
			};
			DrawBasicShapes(vertexBuffer, GL_TRIANGLE_STRIP, 4);
		}
	}

#if 0

	void CShapeRenderer::DrawRectangleWH(float x, float y, float w, float h, bool fill) {
		SDL_FRect rect { x, y, w, h };
		(fill ? SDL_RenderFillRectF : SDL_RenderDrawRectF)(m_sdlRenderer, & rect);
	}
#endif
}