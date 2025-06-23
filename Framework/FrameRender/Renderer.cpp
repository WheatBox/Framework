#include "Renderer.h"

#include "../FrameRender/DefaultShaders.h"

#include "../FrameAsset/Sprite.h"
#include "../FrameRender/Shader.h"
#include "../FrameCore/Camera.h"
#include "../FrameCore/Globals.h" // for gShaderInUsing & gCamera
#include "../FrameCore/Log.h"
#include "../FrameRender/RendererBase.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	CRenderer::CRenderer()
		: m_pDefaultShader { new CShader {} }
		, m_pDefaultInstanceShader { new CShader {} }
	{}

	CRenderer::~CRenderer() {
		delete m_pDefaultShader;
		delete m_pDefaultInstanceShader;
	}

	void EnableInstancingVertexAttribArrays() {
		for(int i = 0; i < 3 + 3 + 1; i++) {
			glEnableVertexAttribArray(3 + i);
		}
	}

	void DisableInstancingVertexAttribArrays() {
		for(int i = 0; i < 3 + 3 + 1; i++) {
			glDisableVertexAttribArray(3 + i);
		}
	}

	void CRenderer::Initialize() {

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		unsigned int indices[] = {
			1, 0, 3, 2
		};

		glGenBuffers(1, & m_VBO);
		glGenBuffers(1, & m_instanceVBO);
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

		RendererBase::BindVBO(m_instanceVBO);

		GLsizei instancedStride = (9 + 2 + 2 + 4) * (GLsizei)sizeof(float);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, instancedStride, (void *)0);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, instancedStride, (void *)(3 * sizeof(float)));
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, instancedStride, (void *)(6 * sizeof(float)));
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, instancedStride, (void *)(9 * sizeof(float)));
		glVertexAttribDivisor(6, 1);

		glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, instancedStride, (void *)(13 * sizeof(float)));
		glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, instancedStride, (void *)(15 * sizeof(float)));
		glVertexAttribDivisor(7, 1);
		glVertexAttribDivisor(8, 1);

		RendererBase::BindVBO(0);

		pShapeRenderer = new CShapeRenderer { this };
		pTextRenderer = new CTextRenderer { this };

		if(!m_pDefaultShader->CompileFiles(DEFAULT_SPRITE_SHADER_FILES)) {
			Log::Log(Log::ELevel::Error, "Failed to load or compile default sprite shader files: %s; %s; So now using in-build default sprite shaders", DEFAULT_SPRITE_SHADER_FILES);
			m_pDefaultShader->Compile(DEFAULT_SPRITE_SHADER);
		}
		m_pDefaultShader->SetUniformInt("u_BaseTexture", 0);

		if(!m_pDefaultInstanceShader->CompileFiles(DEFAULT_INSTANCE_SPRITE_SHADER_FILES)) {
			Log::Log(Log::ELevel::Error, "Failed to load or compile default instance sprite shader files: %s; %s; So now using in-build default instance sprite shaders", DEFAULT_INSTANCE_SPRITE_SHADER_FILES);
			m_pDefaultInstanceShader->Compile(DEFAULT_INSTANCE_SPRITE_SHADER);
		}
		m_pDefaultInstanceShader->SetUniformInt("u_BaseTexture", 0);

		SetShader(m_pDefaultShader);
		SetInstanceShader(m_pDefaultInstanceShader);

		glActiveTexture(GL_TEXTURE0);
	}

	void CRenderer::RenderBegin() {
		Clear(m_backgroundColor, 1.f);
	}

	void CRenderer::RenderEnd() {
	}

	void CRenderer::SetShaderProjectionMatrix(const CShader * pShader) const {
		const Vec2 viewSize = Vec2Cast<float>(gCamera->GetViewSize());
		
		pShader->SetUniformMat3("u_mProj", (
			Matrix33::CreateScale(Vec2 { 2.f / viewSize.x, -2.f / viewSize.y } * gCamera->GetZoom())
			* Matrix33::CreateRotationZ(gCamera->GetViewRotation())
			* Matrix33::CreateTranslation(-gCamera->GetPos())
			).data);
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

	void CRenderer::DrawTexture(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer, const CShader * _pShader) {
		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertexBuffer.m_data), textureVertexBuffer.m_data, GL_DYNAMIC_DRAW);

		RendererBase::BindVBO(0);

		RendererBase::BindTextureId(textureId);

		_pShader->Use();
		SetShaderProjectionMatrix(_pShader);
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

	void CRenderer::DrawSprite(const SSpriteImage * pSpriteImage, const Vec2 & vPos, const Vec2 & vScale, float rotation, STextureVertexBuffer & textureVertexBuffer) {
		Vec2 vTL = pSpriteImage->GetTopLeftOffset() * vScale;
		Vec2 vTR = pSpriteImage->GetTopRightOffset() * vScale;
		Vec2 vBL = pSpriteImage->GetBottomLeftOffset() * vScale;
		Vec2 vBR = pSpriteImage->GetBottomRightOffset() * vScale;
		
		Rotate2DVectors(rotation, { & vTL, & vTR, & vBL, & vBR });

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

	/* +-----------------------------------------------+ */
	/* |             Draw Sprites Instanced            | */
	/* +-----------------------------------------------+ */

	void CRenderer::DrawTexturesInstanced(unsigned int textureId, const STextureVertexBuffer & textureVertexBuffer, const std::vector<SInstanceBuffer> & instances, const CShader * _pShader) {
		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertexBuffer.m_data), textureVertexBuffer.m_data, GL_DYNAMIC_DRAW);

		RendererBase::BindVBO(m_instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SInstanceBuffer) * instances.size(), instances.data(), GL_DYNAMIC_DRAW);

		RendererBase::BindVBO(0);

		RendererBase::BindTextureId(textureId);

		EnableInstancingVertexAttribArrays();

		_pShader->Use();
		SetShaderProjectionMatrix(_pShader);
		glDrawElementsInstanced(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL, static_cast<GLsizei>(instances.size()));

		DisableInstancingVertexAttribArrays();
	}

	void CRenderer::DrawSpritesInstanced(const SSpriteImage * pSpriteImage, const std::vector<SInstanceBuffer> & instances, STextureVertexBuffer & textureVertexBuffer) {
		textureVertexBuffer.SetPositions(
			pSpriteImage->GetTopLeftOffset(),
			pSpriteImage->GetBottomRightOffset()
		);
		textureVertexBuffer.SetTexCoord(pSpriteImage->GetUVLeftTop(), pSpriteImage->GetUVRightBottom());

		DrawTexturesInstanced(pSpriteImage->GetTextureId(), textureVertexBuffer, instances);
	}

}