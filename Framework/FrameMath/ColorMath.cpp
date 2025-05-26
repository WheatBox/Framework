#include "ColorMath.h"

#include "../FrameMath/Math.h"
#include <algorithm>

namespace Frame {

	constexpr void ColorRGB2HSV(uint8 r, uint8 g, uint8 b, uint16 * destH, uint8 * destS, uint8 * destV) {
		float r1 = static_cast<float>(r) / 255.0f;
		float g1 = static_cast<float>(g) / 255.0f;
		float b1 = static_cast<float>(b) / 255.0f;

		float v = std::max({ r1, g1, b1 });
		float v_minus_min = v - std::min({ r1, g1, b1 });

		* destV = static_cast<uint8>(v);
		* destS = (v == 0) ? 0 : static_cast<uint8>(v_minus_min / v);

		uint16 h = 0;
		
		if(v_minus_min == 0) {

		} else if(v == r1) {
			h = static_cast<uint16>(60.f * (g1 - b1) / v_minus_min);
		} else if(v == g1) {
			h = 120 + static_cast<uint16>(60.f * (b1 - r1) / v_minus_min);
		} else {
			h = 240 + static_cast<uint16>(60.f * (r1 - g1) / v_minus_min);
		}

		if(h < 0) {
			h += 360;
		}

		* destH = h;
	}

	constexpr void ColorHSV2RGB(uint16 h, uint8 s, uint8 v, uint8 * destR, uint8 * destG, uint8 * destB) {
		float v1f = static_cast<float>(v) / 100.f;
		float s1f = static_cast<float>(s) / 100.f;

		float h_div_60 = h / 60.f;
		uint8 i = static_cast<uint8>(Floor(h_div_60));
		float f = h_div_60 - static_cast<float>(i);

		uint8 resp = static_cast<uint8>(Floor(v1f * (1.f - s1f) * 255.f));
		uint8 resq = static_cast<uint8>(Floor(v1f * (1.f - f * s1f) * 255.f));
		uint8 rest = static_cast<uint8>(Floor(v1f * (1.f - (1.f - f) * s1f) * 255.f));
		uint8 resv = static_cast<uint8>(Floor(v1f * 255.f));

		switch(i) {
		case 0:
			* destR = resv;
			* destG = rest;
			* destB = resp;
			return;
		case 1:
			* destR = resq;
			* destG = resv;
			* destB = resp;
			return;
		case 2:
			* destR = resp;
			* destG = resv;
			* destB = rest;
			return;
		case 3:
			* destR = resp;
			* destG = resq;
			* destB = resv;
			return;
		case 4:
			* destR = rest;
			* destG = resp;
			* destB = resv;
			return;
		case 5:
			* destR = resv;
			* destG = resp;
			* destB = resq;
			return;
		}

		* destR = 0;
		* destG = 0;
		* destB = 0;
	}

	/* ------ ColorRGB ------ */

	ColorRGB::ColorRGB(const ColorBGR & bgr) {
		Set(bgr);
	}

	ColorRGB::ColorRGB(const ColorHSV & hsv) {
		Set(hsv);
	}

	ColorRGB::operator ColorBGR() const { return ToBGR(); }

	ColorRGB::operator ColorHSV() const { return ToHSV(); }

	void ColorRGB::Set(const ColorBGR & bgr) {
		r = bgr.r;
		g = bgr.g;
		b = bgr.b;
	}

	void ColorRGB::Set(const ColorHSV & hsv) {
		* this = hsv.ToRGB();
	}

	ColorBGR ColorRGB::ToBGR() const {
		return { b, g, r };
	}

	ColorHSV ColorRGB::ToHSV() const {
		uint16 h;
		uint8 s, v;
		ColorRGB2HSV(r, g, b, & h, & s, & v);
		return { h, s, v };
	}

	/* ------ ColorBGR ------ */

	ColorBGR::ColorBGR(const ColorRGB & rgb) {
		Set(rgb);
	}

	ColorBGR::ColorBGR(const ColorHSV & hsv) {
		Set(hsv);
	}

	ColorBGR::operator ColorRGB() const { return ToRGB(); }

	ColorBGR::operator ColorHSV() const { return ToHSV(); }

	void ColorBGR::Set(const ColorRGB & rgb) {
		b = rgb.b;
		g = rgb.g;
		r = rgb.r;
	}

	void ColorBGR::Set(const ColorHSV & hsv) {
		* this = hsv.ToBGR();
	}

	ColorRGB ColorBGR::ToRGB() const {
		return { r, g, b };
	}

	ColorHSV ColorBGR::ToHSV() const {
		uint16 h;
		uint8 s, v;
		ColorRGB2HSV(r, g, b, & h, & s, & v);
		return { h, s, v };
	}

	/* ------ ColorHSV ------ */

	ColorHSV::ColorHSV(const ColorRGB & rgb) {
		Set(rgb);
	}

	ColorHSV::ColorHSV(const ColorBGR & bgr) {
		Set(bgr);
	}

	ColorHSV::operator ColorRGB() const { return ToRGB(); }

	ColorHSV::operator ColorBGR() const { return ToBGR(); }

	void ColorHSV::Set(const ColorRGB & rgb) {
		ColorRGB2HSV(rgb.r, rgb.g, rgb.b, & h, & s, & v);
	}

	void ColorHSV::Set(const ColorBGR & bgr) {
		ColorRGB2HSV(bgr.r, bgr.g, bgr.b, & h, & s, & v);
	}

	ColorRGB ColorHSV::ToRGB() const {
		uint8 r, g, b;
		ColorHSV2RGB(h, s, v, & r, & g, & b);
		return { r, g, b };
	}

	ColorBGR ColorHSV::ToBGR() const {
		uint8 r, g, b;
		ColorHSV2RGB(h, s, v, & r, & g, & b);
		return { b, g, r };
	}

};