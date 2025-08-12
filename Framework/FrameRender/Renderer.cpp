#include "Renderer.h"

#include "DefaultShaders.h"
#include "RendererBase.h"

#include "../FrameAsset/Sprite.h"
#include "../FrameRender/Shader.h"
#include "../FrameCore/Camera.h"
#include "../FrameCore/Globals.h" // for gCamera
#include "../FrameCore/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Frame {

	static CShader * pDefaultShader = nullptr;

	void CRenderer::SetBlendEnable(bool enable) const {
		m_pRenderQueue->Render();
		(enable ? glEnable : glDisable)(GL_BLEND);
	}

	void CRenderer::SetBlendFunc(EBlendFactor src, EBlendFactor dst) const {
		m_pRenderQueue->Render();
		glBlendFunc(static_cast<int>(src), static_cast<int>(dst));
	}

	void CRenderer::SetBlendFunc(EBlendFactor srcColor, EBlendFactor dstColor, EBlendFactor srcAlpha, EBlendFactor dstAlpha) const {
		m_pRenderQueue->Render();
		glBlendFuncSeparate(static_cast<int>(srcColor), static_cast<int>(dstColor), static_cast<int>(srcAlpha), static_cast<int>(dstAlpha));
	}

	void CRenderer::SetBlendEquation(EBlendEquation equation) const {
		m_pRenderQueue->Render();
		glBlendEquation(static_cast<int>(equation));
	}

	void CRenderer::SetBlendEquation(EBlendEquation colorEquation, EBlendEquation alphaEquation) const {
		m_pRenderQueue->Render();
		glBlendEquationSeparate(static_cast<int>(colorEquation), static_cast<int>(alphaEquation));
	}

	void CRenderer::Initialize() {

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);

		m_pRenderQueue = new CRenderQueue;

		SetBlendEnable(true);
		SetBlendFuncDefault();

		pShapeRenderer = new CShapeRenderer { this };
		pTextRenderer = new CTextRenderer { this };

		if(!pDefaultShader) {
			pDefaultShader = new CShader;
			if(!pDefaultShader->CompileFiles(DEFAULT_SPRITE_SHADER_FILES)) {
				Log::Log(Log::ELevel::Error, "Failed to load or compile default sprite shader files: %s; %s; So now using in-build default sprite shaders", DEFAULT_SPRITE_SHADER_FILES);
				pDefaultShader->Compile(DEFAULT_SPRITE_SHADER);
			}
		}
		SetShader(pDefaultShader);
		SetUniformInt("u_BaseTexture", 0);

		glActiveTexture(GL_TEXTURE0);
	}

	void CRenderer::RenderBegin() const {
		Clear(m_backgroundColor, 1.f);
	}

	void CRenderer::RenderEnd() const {
		m_pRenderQueue->Render();
	}

	void CRenderer::Clear(ColorRGB color, float alpha) const {
		m_pRenderQueue->Render();
		glClearColor(ONERGB(color), alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void CRenderer::ResetShader() {
		SetShader(pDefaultShader);
	}

	void CRenderer::SetShader(const CShader * pShader) {
		m_pShader = pShader;
		__UseShader();
	}

	const CShader * CRenderer::GetShader() const {
		return m_pShader;
	}

	void CRenderer::__UseShader(const CShader * pShader) {
		if(m_pUsingShader != pShader) {
			m_pRenderQueue->Render();
			m_pRenderQueue->m_pUsingShader = m_pUsingShader = pShader;
			glUseProgram(m_pUsingShader->GetGlProgramId());
		}
	}

	void CRenderer::__UseShader() {
		__UseShader(m_pShader);
	}

	static void __SetUniformMat3(const CShader * pShader, const char * szUniformName, const float * values) {
		glUniformMatrix3fv(glGetUniformLocation(pShader->GetGlProgramId(), szUniformName), 1, GL_FALSE, values);
	}
	static void __SetUniformProjMat_(const CShader * pShader) {
		__SetUniformMat3(pShader, "u_mProj", gCamera->CreateProjectionMatrix().data);
	}

	void CRenderer::__SetUniformProjMat() const {
		SetUniformMat3("u_mProj", gCamera->CreateProjectionMatrix().data);
	}

	void CRenderer::SetUniformInt(const char * szUniformName, int value) const {
		m_pRenderQueue->Render();
		glUniform1i(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), value);
	}

	void CRenderer::SetUniformFloat(const char * szUniformName, float value) const {
		m_pRenderQueue->Render();
		glUniform1f(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), value);
	}

	void CRenderer::SetUniformVec2(const char * szUniformName, float value0, float value1) const {
		m_pRenderQueue->Render();
		glUniform2f(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), value0, value1);
	}

	void CRenderer::SetUniformVec3(const char * szUniformName, float value0, float value1, float value2) const {
		m_pRenderQueue->Render();
		glUniform3f(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), value0, value1, value2);
	}

	void CRenderer::SetUniformVec4(const char * szUniformName, float value0, float value1, float value2, float value3) const {
		m_pRenderQueue->Render();
		glUniform4f(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), value0, value1, value2, value3);
	}

	void CRenderer::SetUniformMat3(const char * szUniformName, const float * values) const {
		m_pRenderQueue->Render();
		__SetUniformMat3(m_pUsingShader, szUniformName, values);
	}

	void CRenderer::SetUniformMat4(const char * szUniformName, const float * values) const {
		m_pRenderQueue->Render();
		glUniformMatrix4fv(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), 1, GL_FALSE, values);
	}

	void CRenderer::SetUniformIntArray(const char * szUniformName, int count, const int * values) const {
		m_pRenderQueue->Render();
		glUniform1iv(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), count, values);
	}

	void CRenderer::SetUniformFloatArray(const char * szUniformName, int count, const float * values) const {
		m_pRenderQueue->Render();
		glUniform1fv(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), count, values);
	}

	void CRenderer::SetUniformVec2Array(const char * szUniformName, int count, const float * values) const {
		m_pRenderQueue->Render();
		glUniform2fv(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), count, values);
	}

	void CRenderer::SetUniformVec3Array(const char * szUniformName, int count, const float * values) const {
		m_pRenderQueue->Render();
		glUniform3fv(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), count, values);
	}

	void CRenderer::SetUniformVec4Array(const char * szUniformName, int count, const float * values) const {
		m_pRenderQueue->Render();
		glUniform4fv(glGetUniformLocation(m_pUsingShader->GetGlProgramId(), szUniformName), count, values);
	}

	void CRenderer::DrawSpriteTransform(const SSpriteImage * pImage, const Matrix33 & transform, ColorRGB blend, float alpha) {
		__UseShader();
		
		SInstanceBuffer buffer {
			transform * Matrix33::CreateTransformTS(-pImage->GetOrigin(), Vec2Cast<float>(pImage->GetSize())),
			{
				static_cast<float>(blend.r) / 255.f,
				static_cast<float>(blend.g) / 255.f,
				static_cast<float>(blend.b) / 255.f,
				alpha
			},
			pImage->GetUVLeftTop(),
			pImage->GetUVRightBottom()
		};
		m_pRenderQueue->Instance(pImage->GetTextureId(), std::move(buffer));
	}

	CRenderer::CRenderQueue::CRenderQueue() {
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

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * (GLsizei)sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		RendererBase::BindVBO(m_instanceVBO);

		GLsizei instancedStride = (9 + 4 + 4) * (GLsizei)sizeof(float);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, instancedStride, (void *)0);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, instancedStride, (void *)(3 * sizeof(float)));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, instancedStride, (void *)(6 * sizeof(float)));
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);

		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, instancedStride, (void *)(9 * sizeof(float)));
		glVertexAttribDivisor(4, 1);

		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, instancedStride, (void *)(13 * sizeof(float)));
		glVertexAttribDivisor(5, 1);

		RendererBase::BindVBO(0);
	}

	static void EnableInstancingVertexAttribArrays() {
		for(int i = 1; i <= 5; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	static void DisableInstancingVertexAttribArrays() {
		for(int i = 1; i <= 5; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void CRenderer::CRenderQueue::Instance(unsigned int texId, SInstanceBuffer && buffer) {
		if(texId != m_currTexId) {
			Render();
			m_currTexId = texId;
		}
		m_instances.push_back(std::move(buffer));
	}

	void CRenderer::CRenderQueue::Render() {
		if(m_instances.empty()) {
			return;
		}

		__SetUniformProjMat_(m_pUsingShader);

		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);
		constexpr float vertexBuffer[] {
			0.f, 1.f, // Top Left
			1.f, 1.f, // Top Right
			0.f, 0.f, // Bottom Left
			1.f, 0.f, // Bottom Right
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_DYNAMIC_DRAW);

		RendererBase::BindVBO(m_instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SInstanceBuffer) * m_instances.size(), m_instances.data(), GL_DYNAMIC_DRAW);

		RendererBase::BindVBO(0);

		RendererBase::BindTextureId(m_currTexId);

		EnableInstancingVertexAttribArrays();

		glDrawElementsInstanced(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL, static_cast<GLsizei>(m_instances.size()));

		DisableInstancingVertexAttribArrays();

		m_currTexId = 0;
		m_instances.clear();
	}

}