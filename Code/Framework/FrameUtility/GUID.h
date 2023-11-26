#pragma once

#include <FrameCore/BasicTypes.h>

namespace Frame {

	struct GUID {
		uint64 high = 0;
		uint64 low = 0;

		GUID() = default;
		GUID(const char * sz) {
			Set(sz);
		}
		virtual ~GUID() = default;

		void Set(const char * guid) {
			uint8 val;
			uint8 i = 31;
			for(const char * pCurrentChar = guid; * pCurrentChar && i >= 0; pCurrentChar++) {
				if(* pCurrentChar >= '0' && * pCurrentChar <= '9') {
					val = (* pCurrentChar) - '0';
				} else if(* pCurrentChar >= 'A' && * pCurrentChar <= 'F') {
					val = (* pCurrentChar) - 'A' + 10;
				} else if(* pCurrentChar >= 'a' && * pCurrentChar <= 'f') {
					val = (* pCurrentChar) - 'a' + 10;
				} else {
					continue;
				}

				if(i >= 16) {
					high |= static_cast<uint64>(val) << ((i - 16) * 4);
				} else {
					low |= static_cast<uint64>(val) << (i * 4);
				}
				i--;
			}
		}

		bool operator ==(const GUID & guid) const {
			return guid.high == high && guid.low == low;
		}
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