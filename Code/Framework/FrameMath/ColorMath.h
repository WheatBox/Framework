#pragma once

#include <FrameCore/BasicTypes.h>

#define ONECOL(_color_value) (_color_value / 255.f)
#define ONERGB(_ColorRGB) ONECOL(_ColorRGB.r), ONECOL(_ColorRGB.g), ONECOL(_ColorRGB.b)

namespace Frame {

	constexpr int ColorUniteRGB(uint8 r, uint8 g, uint8 b) {
		return ((r << 16) | (g << 8) | b);
	}
	constexpr void ColorSplitRGB(int rgb, uint8 * destR, uint8 * destG, uint8 * destB) {
		* destR = (rgb >> 16) & 0b11111111;
		* destG = (rgb >> 8) & 0b11111111;
		* destB = rgb & 0b11111111;
	}

	constexpr int ColorUniteBGR(uint8 b, uint8 g, uint8 r) {
		return ((b << 16) | (g << 8) | r);
	}
	constexpr void ColorSplitBGR(int bgr, uint8 * destB, uint8 * destG, uint8 * destR) {
		* destB = (bgr >> 16) & 0b11111111;
		* destG = (bgr >> 8) & 0b11111111;
		* destR = (bgr) & 0b11111111;
	}

	constexpr void ColorRGB2HSV(uint8 r, uint8 g, uint8 b, uint16 * destH, uint8 * destS, uint8 * destV);
	constexpr void ColorHSV2RGB(uint16 h, uint8 s, uint8 v, uint8 * destR, uint8 * destG, uint8 * destB);

	struct ColorRGB;
	struct ColorBGR;
	struct ColorHSV;

	/* ------ ColorRGB ------ */

	struct ColorRGB {

		ColorRGB() { r = 0; g = 0; b = 0; }
		ColorRGB(uint8 _r, uint8 _g, uint8 _b) { r = _r; g = _g; b = _b; }
		ColorRGB(int rgb) { ColorSplitRGB(rgb, & r, & g, & b); }
		ColorRGB(const ColorBGR & bgr);
		ColorRGB(const ColorHSV & hsv);

		ColorRGB & operator =(const int & rgb) { ColorSplitRGB(rgb, & r, & g, & b); return * this; }
		ColorRGB & operator =(const ColorBGR & bgr) { Set(bgr); return * this; }
		ColorRGB & operator =(const ColorHSV & hsv) { Set(hsv); return * this; }

		operator int() const { return ColorUniteRGB(r, g, b); }
		operator ColorBGR() const;
		operator ColorHSV() const;

		int Get() const { return ColorUniteRGB(r, g, b); }

		void Set(uint8 _r, uint8 _g, uint8 _b) { r = _r; g = _g; b = _b; }
		void Set(int rgb) { ColorSplitRGB(rgb, & r, & g, & b); }

		void Set(const ColorBGR & bgr);
		void Set(const ColorHSV & hsv);

		ColorBGR ToBGR() const;
		ColorHSV ToHSV() const;

		uint8 r; // 0 ~ 255
		uint8 g; // 0 ~ 255
		uint8 b; // 0 ~ 255
	};

	/* ------ ColorBGR ------ */

	struct ColorBGR {

		ColorBGR() { b = 0; g = 0; r = 0; }
		ColorBGR(uint8 _b, uint8 _g, uint8 _r) { b = _b; g = _g; r = _r; }
		ColorBGR(int bgr) { ColorSplitBGR(bgr, & b, & g, & r); }
		ColorBGR(const ColorRGB & rgb);
		ColorBGR(const ColorHSV & hsv);

		ColorBGR & operator =(const int & bgr) { ColorSplitBGR(bgr, & b, & g, & r); return * this; }
		ColorBGR & operator =(const ColorRGB & rgb) { Set(rgb); return * this; }
		ColorBGR & operator =(const ColorHSV & hsv) { Set(hsv); return * this; }

		operator int() const { return ColorUniteBGR(b, g, r); }
		operator ColorRGB() const;
		operator ColorHSV() const;

		unsigned int Get() const { return ColorUniteBGR(b, g, r); }

		void Set(uint8 _b, uint8 _g, uint8 _r) { b = _b; g = _g; r = _r; }
		void Set(int bgr) { ColorSplitBGR(bgr, & b, & g, & r); }

		void Set(const ColorRGB & rgb);
		void Set(const ColorHSV & hsv);

		ColorRGB ToRGB() const;
		ColorHSV ToHSV() const;

		uint8 b; // 0 ~ 255
		uint8 g; // 0 ~ 255
		uint8 r; // 0 ~ 255
	};

	/* ------ ColorHSV ------ */

	struct ColorHSV {

		ColorHSV() { h = 0; s = 0; v = 0; }
		ColorHSV(uint16 _h, uint8 _s, uint8 _v) { h = _h; s = _s; v = _v; }
		ColorHSV(const ColorRGB & rgb);
		ColorHSV(const ColorBGR & bgr);

		ColorHSV & operator =(const ColorRGB & rgb) { Set(rgb); return * this; }
		ColorHSV & operator =(const ColorBGR & bgr) { Set(bgr); return * this; }

		operator ColorRGB() const;
		operator ColorBGR() const;

		void Set(uint16 _h, uint8 _s, uint8 _v) { h = _h; s = _s; v = _v; }

		void Set(const ColorRGB & rgb);
		void Set(const ColorBGR & bgr);

		ColorRGB ToRGB() const;
		ColorBGR ToBGR() const;

		uint16 h; // 0 ~ 359
		uint8 s; // 0 ~ 100
		uint8 v; // 0 ~ 100
	};

};