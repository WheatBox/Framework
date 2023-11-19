#pragma once

#include <cmath>

namespace Frame {

	constexpr float pi_f            = 3.1415926535897932f;
	constexpr float degToRadRatio_f = 0.0174532925199433f;
	constexpr float radToDegRatio_f = 57.295779513082321f;

	constexpr double pi_d            = 3.1415926535897932;
	constexpr double degToRadRatio_d = 0.0174532925199433;
	constexpr double radToDegRatio_d = 57.295779513082321;

	template<typename T>
	constexpr auto DegToRad(T && deg) {
		return deg * degToRadRatio_f;
	}

	constexpr double DegToRad(double deg) {
		return deg * degToRadRatio_d;
	}

	template<typename T>
	constexpr auto RadToDeg(T && rad) {
		return rad * radToDegRatio_f;
	}

	constexpr double RadToDeg(double rad) {
		return rad * radToDegRatio_d;
	}

	constexpr int Floor(float n) {
		return static_cast<int>(n) - (n < 0.f);
	}
	constexpr int Floor(double n) {
		return static_cast<int>(n) - (n < 0.0);
	}

	template<typename T>
	constexpr auto Clamp(T n, T low, T high) {
		if(n < low) {
			return low;
		} else if(n > high) {
			return high;
		}
		return n;
	}

}