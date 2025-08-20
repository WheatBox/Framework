#pragma once

#include "../FrameCore/BasicTypes.h"

namespace Frame {

	struct GUID final {
		uint64 high = 0;
		uint64 low = 0;

		GUID() = default;
		GUID(const char * sz) {
			Set(sz);
		}

		bool operator ==(const GUID & guid) const {
			return guid.high == high && guid.low == low;
		}

		void Set(const char * szGuid);

		// UUID v4
		static GUID Generate();
	};

}

#include <unordered_map>

namespace std {
	template<>
	struct hash<Frame::GUID> {
		size_t operator ()(const Frame::GUID & guid) const noexcept {
			std::hash<uint64> hasher {};
			return hasher(guid.high) ^ hasher(guid.low);
		}
	};
}