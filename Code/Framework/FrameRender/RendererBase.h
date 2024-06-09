#pragma once

#include <FrameMath/ColorMath.h>

#include <tuple>

namespace Frame::RendererBase {
	
	struct IColorAlpha {
	public:
		void SetColor(const ColorRGB & rgb) {
			m_color = rgb;
		}
		void SetColor(uint8 r, uint8 g, uint8 b) {
			SetColor({ r, g, b });
		}
		void SetAlpha(float alpha) {
			m_alpha = alpha;
		}
		void SetColorAlpha(const ColorRGB & rgb, float alpha) {
			m_color = rgb;
			m_alpha = alpha;
		}
		void SetColorAlpha(uint8 r, uint8 g, uint8 b, float alpha) {
			SetColorAlpha({ r, g, b }, alpha);
		}

		const ColorRGB & GetColor() const { return m_color; }
		float GetAlpha() const { return m_alpha; }
		std::pair<ColorRGB, float> GetColorAlpha() const {
			return { m_color, m_alpha };
		}

	protected:
		ColorRGB m_color { 255, 255, 255 };
		float m_alpha = 1.f;
	};

	void BindVAO(unsigned int VAO);
	void BindVBO(unsigned int VBO);
	void BindTextureId(unsigned int textureId);

}
