#include <FrameRender/Renderer.h>

#include <FrameAsset/Sprite.h>
#include <FrameRender/Shader.h>
#include <FrameCore/Globals.h> // for gShaderInUsing

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	void CRenderer::Initialize(int windowWidth, int windowHeight, Shader * _pSpriteShader, Shader * _pSolidColorShader) {

		FramebufferResizeCallback(windowWidth, windowHeight);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		unsigned int indices[] = {
			2, 1, 0,
			1, 2, 3
		};

		glGenBuffers(1, & m_VBO);
		glGenVertexArrays(1, & m_VAO);
		glGenBuffers(1, & m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
		
		GLsizei stride = (3 + 4 + 2) * (GLsizei)sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		pShapeRenderer = new CShapeRenderer { this };
		// pTextRenderer = new CTextRenderer { & m_color, & m_alpha };

		pSpriteShader = _pSpriteShader;
		pSolidColorShader = _pSolidColorShader;

		pSpriteShader->Use();

		glActiveTexture(GL_TEXTURE0);
	}

	void CRenderer::FramebufferResizeCallback(int width, int height) {
		m_windowWidth = width;
		m_windowHeight = height;
	}

	void CRenderer::RenderBegin() {
		glClearColor(ONERGB(m_backgroundColor), 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void CRenderer::RenderEnd() {
	}

	/* +-----------------------------------------------+ */
	/* |                Set Draw Params                | */
	/* +-----------------------------------------------+ */

	/*void CRenderer::SetBlendMode(EBlendMode blendMode) {
		//TODO
	}*/

	/* +-----------------------------------------------+ */
	/* |                  Draw Sprite                  | */
	/* +-----------------------------------------------+ */

	void CRenderer::DrawTexture(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer) {
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertexBuffer.m_data), textureVertexBuffer.m_data, GL_DYNAMIC_DRAW);

		glBindTexture(GL_TEXTURE_2D, textureId);
		pSpriteShader->Use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

	void CRenderer::DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, STextureVertexBuffer & textureVertexBuffer) {
		textureVertexBuffer.SetPositions(
			Project(vPos + pSprite->GetTopLeftOffset()),
			Project(vPos + pSprite->GetBottomRightOffset())
		);

		DrawTexture(pSprite->GetTextureId(), textureVertexBuffer);
	}

	void CRenderer::DrawSprite(CStaticSprite * pSprite, const Vec2 & vPos, const Vec2 & vScale, float angle, STextureVertexBuffer & textureVertexBuffer) {
		Vec2 vTL = pSprite->GetTopLeftOffset();
		Vec2 vTR = pSprite->GetTopRightOffset();
		Vec2 vBL = pSprite->GetBottomLeftOffset();
		Vec2 vBR = pSprite->GetBottomRightOffset();
		
		Rotate2DVectorsDegree(angle, vTL, vTR, vBL, vBR);

		textureVertexBuffer.SetPositions(
			Project(vPos + vTL * vScale),
			Project(vPos + vTR * vScale),
			Project(vPos + vBL * vScale),
			Project(vPos + vBR * vScale)
		);

		DrawTexture(pSprite->GetTextureId(), textureVertexBuffer);
	}

}