#pragma once

#include "ShapeRenderer.h"
#include "TextRenderer.h"

#include "../FrameMath/ColorMath.h"
#include "../FrameMath/Matrix33.h"

struct GLFWwindow;

namespace Frame {

	struct SSpriteImage;

	class CShader;

	class CRenderer final {
	public:

		enum class EBlendFactor {
			Zero = 0, // GL_ZERO
			One = 1, // GL_ONE
			SrcColor = 0x0300, // GL_SRC_COLOR
			OneMinusSrcColor = 0x0301, // GL_ONE_MINUS_SRC_COLOR
			SrcAlpha = 0x0302, // GL_SRC_ALPHA
			OneMinusSrcAlpha = 0x0303, // GL_ONE_MINUS_SRC_ALPHA
			DstAlpha = 0x0304, // GL_DST_ALPHA
			OneMinusDstAlpha = 0x0305, // GL_ONE_MINUS_DST_ALPHA
			DstColor = 0x0306, // GL_DST_COLOR
			OneMinusDstColor = 0x0307, // GL_ONE_MINUS_DST_COLOR
			SrcAlphaSaturate = 0x0308, // GL_SRC_ALPHA_SATURATE
		};

		enum class EBlendEquation {
			Add = 0x8006, // GL_FUNC_ADD
			ReverseSubtract = 0x800A, // GL_FUNC_SUBTRACT
			Subtract = 0x800B, // GL_FUNC_REVERSE_SUBTRACT
		};
		
		void SetBlendEnable(bool enable) const;
		
		void SetBlendFunc(EBlendFactor src, EBlendFactor dst) const;
		void SetBlendFunc(EBlendFactor srcColor, EBlendFactor dstColor, EBlendFactor srcAlpha, EBlendFactor dstAlpha) const;
		void SetBlendFuncDefault() const {
			SetBlendFunc(EBlendFactor::SrcAlpha, EBlendFactor::OneMinusSrcAlpha, EBlendFactor::One, EBlendFactor::OneMinusSrcAlpha);
		}

		void SetBlendEquation(EBlendEquation equation) const;
		void SetBlendEquation(EBlendEquation colorEquation, EBlendEquation alphaEquation) const;
		void SetBlendEquationDefault() const {
			SetBlendEquation(EBlendEquation::Add);
		}

		void Initialize();

		CShapeRenderer * pShapeRenderer = nullptr;
		CTextRenderer * pTextRenderer = nullptr;

	public:
		void RenderBegin() const;
		void RenderEnd() const;

		void Clear(ColorRGB color, float alpha, bool processRenderQueue = true) const;

		void SetBackgroundColor(const ColorRGB & rgb) { m_backgroundColor = rgb; }
		const ColorRGB & GetBackgroundColor() const { return m_backgroundColor; }

		void ResetShader();
		void SetShader(const CShader * pShader);
		const CShader * GetShader() const;

		void __UseShader(const CShader * pShader);
		void __UseShader();
		void __SetUniformProjMat() const;

		void SetUniformInt(const char * szUniformName, int value) const;
		void SetUniformFloat(const char * szUniformName, float value) const;

		void SetUniformVec2(const char * szUniformName, const Vec2 & v) const { SetUniformVec2(szUniformName, v.x, v.y); }
		void SetUniformVec2(const char * szUniformName, float value0, float value1) const;
		void SetUniformVec3(const char * szUniformName, const Vec3 & v) const { SetUniformVec3(szUniformName, v.x, v.y, v.z); }
		void SetUniformVec3(const char * szUniformName, float value0, float value1, float value2) const;
		void SetUniformVec4(const char * szUniformName, float value0, float value1, float value2, float value3) const;

		void SetUniformMat3(const char * szUniformName, const float * values) const;
		void SetUniformMat4(const char * szUniformName, const float * values) const;

		void SetUniformIntArray(const char * szUniformName, int count, const int * values) const;
		void SetUniformFloatArray(const char * szUniformName, int count, const float * values) const;
		void SetUniformVec2Array(const char * szUniformName, int count, const float * values) const;
		void SetUniformVec3Array(const char * szUniformName, int count, const float * values) const;
		void SetUniformVec4Array(const char * szUniformName, int count, const float * values) const;

		void DrawSprite(const SSpriteImage * pImage, const Vec2 & pos, ColorRGB blend = 0xFFFFFF, float alpha = 1.f, const Vec2 & scale = 1.f, float rot = 0.f) {
			DrawSpriteTransform(pImage, Matrix33::CreateTransform(pos, rot, scale), blend, alpha);
		}
		void DrawSpriteTransform(const SSpriteImage * pImage, const Matrix33 & transform, ColorRGB blend = 0xFFFFFF, float alpha = 1.f);

	public:
		struct SInstanceBuffer final {
			Matrix33 transform = Matrix33::CreateIdentity();
			float color[4] { 1.f, 1.f, 1.f, 1.f };
			Vec2 texCoordLT { 0.f, 1.f };
			Vec2 texCoordRB { 1.f, 0.f };
		};
		static_assert(sizeof(SInstanceBuffer) ==
			sizeof(SInstanceBuffer::transform.data)
			+ sizeof(SInstanceBuffer::color)
			+ sizeof(SInstanceBuffer::texCoordLT.x) + sizeof(SInstanceBuffer::texCoordLT.y)
			+ sizeof(SInstanceBuffer::texCoordRB.x) + sizeof(SInstanceBuffer::texCoordRB.y)
			, "ERROR! There is some extra memory in SInstanceBuffer!");

		class CRenderQueue final {
		public:
			CRenderQueue();
			void Instance(unsigned int texId, SInstanceBuffer && buffer);
			void Render();
		private:
			unsigned int m_currTexId = 0;
			std::vector<SInstanceBuffer> m_instances;
			const CShader * m_pCurrShader = nullptr;

			unsigned int m_VBO = 0, m_VAO = 0, m_EBO = 0;
			unsigned int m_instanceVBO = 0;
		public:
			const CShader * m_pUsingShader = nullptr;
		};

		CRenderQueue * GetRenderQueue() const {
			return m_pRenderQueue;
		}

	private:
		ColorRGB m_backgroundColor { 0, 0, 0 };
		CRenderQueue * m_pRenderQueue = nullptr;
		const CShader * m_pShader = nullptr;
		const CShader * m_pUsingShader = nullptr;
	};

}