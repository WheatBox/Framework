#pragma once

#include <FrameCore/BasicTypes.h>

namespace Frame {

	// 1u << pos
	template<typename ResT = Uint32>
	constexpr ResT FlagBit(Uint8 pos) {
		return 1u << pos;
	}

	// 1ull << pos
	constexpr Uint64 FlagBit64(Uint8 pos) {
		return 1ull << pos;
	}

}