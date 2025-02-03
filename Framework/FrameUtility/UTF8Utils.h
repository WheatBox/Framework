#pragma once

#include <FrameCore/BasicTypes.h>

namespace Frame::UTF8Utils {

	constexpr int8 CharacterLength(unsigned char _byte) {
		if(_byte >> 7 == 0) { // 长度 1 个字节 | 1 byte in length
			return 1;
		}
		if(_byte >> 5 == 0b110) { // 长度 2 个字节 | 2 byte in length
			return 2;
		}
		if(_byte >> 4 == 0b1110) { // 长度 3 个字节 | 3 byte in length
			return 3;
		}
		if(_byte >> 3 == 0b11110) { // 长度 4 个字节 | 4 byte in length
			return 4;
		}
		
		// 当前字节并非 Utf-8 字符的首字节
		// The current byte is not the first byte of Utf-8 characters
		return 0;
	}

	constexpr unsigned char RemoveByteHeader(unsigned char _byte, int8 _byte_s_CharacterLength) {
		switch(_byte_s_CharacterLength) {
		case 2:
			return _byte & 0b00011111;
		case 3:
			return _byte & 0b00001111;
		case 4:
			return _byte & 0b00000111;
		}
		return _byte & 0b01111111;
	}
	constexpr unsigned char RemoveByteHeader(unsigned char _byte) {
		return RemoveByteHeader(_byte, CharacterLength(_byte));
	}

	constexpr UnicodeChar ToUnicodeCharacter(const char * utf8Character, int8 _characterLength) {
		switch(_characterLength) {
		case 2:
			return
				  (UnicodeChar { RemoveByteHeader(utf8Character[0], _characterLength) } << 6)
				+  UnicodeChar { RemoveByteHeader(utf8Character[1]) };
		case 3:
			return
				  (UnicodeChar { RemoveByteHeader(utf8Character[0], _characterLength) } << 12)
				+ (UnicodeChar { RemoveByteHeader(utf8Character[1]) } << 6)
				+  UnicodeChar { RemoveByteHeader(utf8Character[2]) };
		case 4:
			return
				  (UnicodeChar { RemoveByteHeader(utf8Character[0], _characterLength) } << 18)
				+ (UnicodeChar { RemoveByteHeader(utf8Character[1]) } << 12)
				+ (UnicodeChar { RemoveByteHeader(utf8Character[2]) } << 6)
				+  UnicodeChar { RemoveByteHeader(utf8Character[3]) };
		}
		return { RemoveByteHeader(utf8Character[0], _characterLength) };
	}
	constexpr UnicodeChar ToUnicodeCharacter(const char * utf8Character) {
		return ToUnicodeCharacter(utf8Character, CharacterLength(utf8Character[0]));
	}

	inline UnicodeString ToUnicode(UTF8StringView strUtf8) {
		UnicodeString strUnicode {};

		size_t len = strUtf8.length();
		strUnicode.reserve(len * 2);
		
		int8 chrLen = 0;
		for(size_t i = 0; i < len; i += (chrLen > 0 ? chrLen : 1)) {
			chrLen = CharacterLength(strUtf8.data()[i]);
			strUnicode += ToUnicodeCharacter(strUtf8.data() + i, chrLen);
		}
		strUnicode.reserve(strUnicode.size());
		
		return strUnicode;
	}

}