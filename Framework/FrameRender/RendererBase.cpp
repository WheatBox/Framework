#include <FrameRender/RendererBase.h>

#include <FrameRender/Renderer.h>

#include <glad/glad.h>

namespace Frame::RendererBase {

	void BindVAO(unsigned int VAO) {
		if(CRenderer::s_currentVAO != VAO) {
			CRenderer::s_currentVAO = VAO;
			glBindVertexArray(VAO);
		}
	}

	void BindVBO(unsigned int VBO) {
		if(CRenderer::s_currentVBO != VBO) {
			CRenderer::s_currentVBO = VBO;
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
		}
	}

	void BindTextureId(unsigned int textureId) {
		if(CRenderer::s_currentTextureId != textureId) {
			CRenderer::s_currentTextureId = textureId;
			glBindTexture(GL_TEXTURE_2D, textureId);
		}
	}

}
