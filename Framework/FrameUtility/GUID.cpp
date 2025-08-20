#include "GUID.h"

#include <random>

namespace Frame {

void GUID::Set(const char * szGuid) {
	uint8 val;
	uint8 i = 31;
	for(const char * pCurrentChar = szGuid; * pCurrentChar && i >= 0; pCurrentChar++) {
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

GUID GUID::Generate() {
	thread_local static std::mt19937_64 gen { std::random_device {}() };
	std::uniform_int_distribution<uint64> dist;

	Frame::GUID guid;

	guid.high = dist(gen);
	guid.low = dist(gen);

	guid.high &= 0xFFFF'FFFF'FFFF'0FFFull;
	guid.high |= 0x0000'0000'0000'4000ull;

	guid.low &= 0x3FFF'FFFF'FFFF'FFFFull;
	guid.low |= 0x8000'0000'0000'0000ull;

	return guid;
}

}