#pragma once

#include <FrameCore/BasicTypes.h>

namespace Frame {

	// 1U << pos
	template<typename ResT = Uint32>
	constexpr ResT FlagBit(Uint8 pos) {
		return 1U << pos;
	}

	// 1ULL << pos
	constexpr Uint64 FlagBit64(Uint8 pos) {
		return 1ULL << pos;
	}

}