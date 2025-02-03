#pragma once

#include <FrameCore/BasicTypes.h>

namespace Frame {

	// 1u << pos
	template<typename ResT = uint32>
	constexpr ResT FlagBit(uint8 pos) {
		return 1u << pos;
	}

	// 1ull << pos
	constexpr uint64 FlagBit64(uint8 pos) {
		return 1ull << pos;
	}

}