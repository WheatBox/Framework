#pragma once

#include <FrameCore/BaseTypes.h>

namespace Frame {

	constexpr int ColorUniteRGB(Uint8 r, Uint8 g, Uint8 b) {
		return ((r << 16) | (g << 8) | b);
	}
	constexpr void ColorSplitRGB(int rgb, Uint8 * destR, Uint8 * destG, Uint8 * destB) {
		* destR = (rgb >> 16) & 0b11111111;
		* destG = (rgb >> 8) & 0b11111111;
		* destB = rgb & 0b11111111;
	}

	constexpr int ColorUniteBGR(Uint8 b, Uint8 g, Uint8 r) {
		return ((b << 16) | (g << 8) | r);
	}
	constexpr void ColorSplitBGR(int bgr, Uint8 * destB, Uint8 * destG, Uint8 * destR) {
		* destB = (bgr >> 16) & 0b11111111;
		* destG = (bgr >> 8) & 0b11111111;
		* destR = (bgr) & 0b11111111;
	}

	constexpr void ColorRGB2HSV(Uint8 r, Uint8 g, Uint8 b, Uint16 * destH, Uint8 * destS, Uint8 * destV);
	constexpr void ColorHSV2RGB(Uint16 h, Uint8 s, Uint8 v, Uint8 * destR, Uint8 * destG, Uint8 * destB);

	struct ColorRGB;
	struct ColorBGR;
	struct ColorHSV;

	/* ------ ColorRGB ------ */

	struct ColorRGB {

		ColorRGB() { r = 0; g = 0; b = 0; }
		ColorRGB(Uint8 _r, Uint8 _g, Uint8 _b) { r = _r; g = _g; b = _b; }
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

		void Set(Uint8 _r, Uint8 _g, Uint8 _b) { r = _r; g = _g; b = _b; }
		void Set(int rgb) { ColorSplitRGB(rgb, & r, & g, & b); }

		void Set(const ColorBGR & bgr);
		void Set(const ColorHSV & hsv);

		ColorBGR ToBGR() const;
		ColorHSV ToHSV() const;

		Uint8 r; // 0 ~ 255
		Uint8 g; // 0 ~ 255
		Uint8 b; // 0 ~ 255
	};

	/* ------ ColorBGR ------ */

	struct ColorBGR {

		ColorBGR() { b = 0; g = 0; r = 0; }
		ColorBGR(Uint8 _b, Uint8 _g, Uint8 _r) { b = _b; g = _g; r = _r; }
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

		void Set(Uint8 _b, Uint8 _g, Uint8 _r) { b = _b; g = _g; r = _r; }
		void Set(int bgr) { ColorSplitBGR(bgr, & b, & g, & r); }

		void Set(const ColorRGB & rgb);
		void Set(const ColorHSV & hsv);

		ColorRGB ToRGB() const;
		ColorHSV ToHSV() const;

		Uint8 b; // 0 ~ 255
		Uint8 g; // 0 ~ 255
		Uint8 r; // 0 ~ 255
	};

	/* ------ ColorHSV ------ */

	struct ColorHSV {

		ColorHSV() { h = 0; s = 0; v = 0; }
		ColorHSV(Uint16 _h, Uint8 _s, Uint8 _v) { h = _h; s = _s; v = _v; }
		ColorHSV(const ColorRGB & rgb);
		ColorHSV(const ColorBGR & bgr);

		ColorHSV & operator =(const ColorRGB & rgb) { Set(rgb); return * this; }
		ColorHSV & operator =(const ColorBGR & bgr) { Set(bgr); return * this; }

		operator ColorRGB() const;
		operator ColorBGR() const;

		void Set(Uint16 _h, Uint8 _s, Uint8 _v) { h = _h; s = _s; v = _v; }

		void Set(const ColorRGB & rgb);
		void Set(const ColorBGR & bgr);

		ColorRGB ToRGB() const;
		ColorBGR ToBGR() const;

		Uint16 h; // 0 ~ 359
		Uint8 s; // 0 ~ 100
		Uint8 v; // 0 ~ 100
	};

};