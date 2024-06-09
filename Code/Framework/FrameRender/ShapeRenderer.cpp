#include <FrameRender/ShapeRenderer.h>

#include <FrameRender/DefaultShaders.h>
#include <FrameRender/Renderer.h>
#include <FrameRender/RendererBase.h>
#include <FrameCore/Log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>

namespace Frame {

	CShapeRenderer::CShapeRenderer(CRenderer * pRenderer)
		: m_pRenderer { pRenderer }
		, m_pDefaultShader { new CShader {} }
	{
		glGenBuffers(1, & m_VBO);
		glGenVertexArrays(1, & m_VAO);

		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);

		GLsizei stride = (3 + 4) * (GLsizei)sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		if(!m_pDefaultShader->CompileFiles(DEFAULT_COLOR_SHADER_FILES)) {
			Log::Log(Log::ELevel::Error, "Failed to load or compile default color shader files: %s; %s; So now using in-build default color shaders", DEFAULT_COLOR_SHADER_FILES);
			m_pDefaultShader->Compile(DEFAULT_COLOR_SHADER);
		}
		SetShader(m_pDefaultShader);
	}

	CShapeRenderer::~CShapeRenderer() {
		delete m_pDefaultShader;
	}

	/* +-----------------------------------------------+ */
	/* |               Draw Basic Shapes               | */
	/* +-----------------------------------------------+ */

	void CShapeRenderer::DrawBasicShapes(float * vertexBuffer, uint8 _GL_mode, int count) {
		RendererBase::BindVAO(m_VAO);
		RendererBase::BindVBO(m_VBO);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * static_cast<size_t>(count * 7), vertexBuffer, GL_DYNAMIC_DRAW);
		m_pShader->Use();
		m_pRenderer->SetShaderProjectionUniforms(m_pShader);
		glDrawArrays(_GL_mode, 0, count);
	}

	void CShapeRenderer::DrawPointBlended(Vec2 vPos, const ColorRGB & rgb, float alpha, float _size) {
		float vertexBuffer[] = { vPos.x, vPos.y, 0.f, ONERGB(rgb), alpha };
		glPointSize(_size);
		DrawBasicShapes(vertexBuffer, GL_POINTS, 1);
	}

	void CShapeRenderer::DrawLineBlended(Vec2 vPos1, Vec2 vPos2, const ColorRGB & rgb1, float alpha1, const ColorRGB & rgb2, float alpha2, float width) {
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

	void CShapeRenderer::DrawTriangleBlended(Vec2 vPos1, Vec2 vPos2, Vec2 vPos3,
		ColorRGB rgb1, float alpha1, ColorRGB rgb2, float alpha2, const ColorRGB & rgb3, float alpha3,
		float outlineWidth
	) {
		if((vPos2 - vPos1).Cross(vPos3 - vPos1) > 0) {
			std::swap(vPos1, vPos2);
			std::swap(rgb1, rgb2);
			std::swap(alpha1, alpha2);
		}

		float vertexBuffer[] = {
			vPos1.x, vPos1.y, 0.f, ONERGB(rgb1), alpha1,
			vPos2.x, vPos2.y, 0.f, ONERGB(rgb2), alpha2,
			vPos3.x, vPos3.y, 0.f, ONERGB(rgb3), alpha3
		};
		if(outlineWidth) {
			glLineWidth(outlineWidth);
			DrawBasicShapes(vertexBuffer, GL_LINE_LOOP, 3);
		} else {
			DrawBasicShapes(vertexBuffer, GL_TRIANGLES, 3);
		}
	}

}