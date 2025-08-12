#include "RendererBase.h"

#include <glad/glad.h>

namespace Frame::RendererBase {

	unsigned int currentVAO = 0;
	unsigned int currentVBO = 0;
	unsigned int currentTextureId = 0;

	void BindVAO(unsigned int VAO) {
		if(currentVAO != VAO) {
			currentVAO = VAO;
			glBindVertexArray(VAO);
		}
	}

	void BindVBO(unsigned int VBO) {
		if(currentVBO != VBO) {
			currentVBO = VBO;
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
		}
	}

	void BindTextureId(unsigned int textureId) {
		if(currentTextureId != textureId) {
			currentTextureId = textureId;
			glBindTexture(GL_TEXTURE_2D, textureId);
		}
	}

}
