﻿#include <FrameRender/Renderer.h>

#include <FrameRender/DefaultShaders.h>

#include <FrameAsset/Sprite.h>
#include <FrameRender/Shader.h>
#include <FrameCore/Camera.h>
#include <FrameCore/Globals.h> // for gShaderInUsing & gCamera
#include <FrameCore/Log.h>
#include <FrameRender/RendererBase.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	CRenderer::CRenderer()
		: m_pDefaultShader { new CShader {} }
	{}

	CRenderer::~CRenderer() {
		delete m_pDefaultShader;
	}

	void CRenderer::Initialize() {

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		unsigned int indices[] = {
			1, 0, 3, 2
		};

		glGenBuffers(1, & m_VBO);
		glGenVertexArrays(1, & m_VAO);
		glGenBuffers(1, & m_EBO);

		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);
		
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
		pTextRenderer = new CTextRenderer { this };

		if(!m_pDefaultShader->CompileFiles(DEFAULT_SPRITE_SHADER_FILES)) {
			Log::Log(Log::ELevel::Error, "Failed to load or compile default sprite shader files: %s; %s; So now using in-build default sprite shaders", DEFAULT_SPRITE_SHADER_FILES);
			m_pDefaultShader->Compile(DEFAULT_SPRITE_SHADER);
		}
		m_pDefaultShader->SetUniformInt("u_BaseTexture", 0);
		SetShader(m_pDefaultShader);

		glActiveTexture(GL_TEXTURE0);
	}

	void CRenderer::RenderBegin() {
		Clear(m_backgroundColor, 1.f);
	}

	void CRenderer::RenderEnd() {
	}

	void CRenderer::SetShaderProjectionUniforms(CShader * pShader) const {
		const Vec2 viewSize = Vec2Cast<float>(gCamera->GetViewSize());
		const Vec2 proj = Vec2 {
			2.f / viewSize.x,
			2.f / viewSize.y
		} * gCamera->GetZoom();
		const Vec2 camPos = gCamera->GetPos();
		pShader->SetUniformVec2("u_vProj", proj.x, proj.y);
		pShader->SetUniformVec2("u_vCamPos", camPos.x, camPos.y);
		pShader->SetUniformFloat("u_fViewRotRad", gCamera->GetViewRotation());
	}

	void CRenderer::Clear(ColorRGB color, float alpha) {
		glClearColor(ONERGB(color), alpha);
		glClear(GL_COLOR_BUFFER_BIT);
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

	void CRenderer::DrawTexture(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer, CShader * _pShader) {
		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertexBuffer.m_data), textureVertexBuffer.m_data, GL_DYNAMIC_DRAW);

		RendererBase::BindTextureId(textureId);

		_pShader->Use();
		SetShaderProjectionUniforms(_pShader);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL);
	}

	void CRenderer::DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, STextureVertexBuffer & textureVertexBuffer) {
		textureVertexBuffer.SetPositions(
			vPos + pSpriteImage->GetTopLeftOffset(),
			vPos + pSpriteImage->GetBottomRightOffset()
		);
		textureVertexBuffer.SetTexCoord(pSpriteImage->GetUVLeftTop(), pSpriteImage->GetUVRightBottom());

		DrawTexture(pSpriteImage->GetTextureId(), textureVertexBuffer);
	}

	void CRenderer::DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const Vec2 & vScale, float angle, STextureVertexBuffer & textureVertexBuffer) {
		Vec2 vTL = pSpriteImage->GetTopLeftOffset() * vScale;
		Vec2 vTR = pSpriteImage->GetTopRightOffset() * vScale;
		Vec2 vBL = pSpriteImage->GetBottomLeftOffset() * vScale;
		Vec2 vBR = pSpriteImage->GetBottomRightOffset() * vScale;
		
		Rotate2DVectorsDegree(angle, { & vTL, & vTR, & vBL, & vBR });

		textureVertexBuffer.SetPositions(vPos + vTL, vPos + vTR, vPos + vBL, vPos + vBR);

		textureVertexBuffer.SetTexCoord(pSpriteImage->GetUVLeftTop(), pSpriteImage->GetUVRightBottom());

		//if(vScale.x * vScale.y < 0.f) {
		//	glFrontFace(GL_CW);
		//	DrawTexture(pSpriteImage->GetTextureId(), textureVertexBuffer);
		//	glFrontFace(GL_CCW);
		//} else {
			DrawTexture(pSpriteImage->GetTextureId(), textureVertexBuffer);
		//}
	}

}