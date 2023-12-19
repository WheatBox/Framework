#pragma once

#include <FrameCore/BasicTypes.h>
#include <FrameMath/Vector2.h>

#include <FrameUtility/UTF8Utils.h>

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>

struct FT_LibraryRec_;
typedef FT_LibraryRec_ * FT_Library;

struct FT_FaceRec_;
typedef FT_FaceRec_ * FT_Face;

namespace Frame {

	class CFont {

	public:
		// Unicode
		typedef UnicodeChar CharType;

		struct SCharacter {
			SCharacter() = default;
			SCharacter(unsigned int _textureId, const Vec2 & _size, const Vec2 & _bearing, const Vec2 & _advance);

			unsigned int textureId = 0;
			unsigned int m_VAO, m_VBO;
			Vec2 size {};
			Vec2 bearing {};
			Vec2 advance {};

			float vertexBuffer[20];
		};

	public:

		CFont() = delete;
		CFont(const char * filename, float fontSize);
		virtual ~CFont();

		SCharacter * InitializeCharacter(CharType _character);
		
		void DestroyCharacter(CharType _character);

		void DestroyAllCharacters();

		SCharacter * GetCharacter(CharType _character) const {
			if(m_characters.find(_character) != m_characters.end()) {
				return m_characters.find(_character)->second;
			}
			return nullptr;
		}

		SCharacter * GetOrInitCharacter(CharType _character) {
			if(m_characters.find(_character) == m_characters.end()) {
				return InitializeCharacter(_character);
			}
			return m_characters.find(_character)->second;
		}

		// 若新的字体大小和旧的字体大小一样，则会跳过执行，什么也不会发生
		// 该函数运行成功后会清空所有的已生成过的字体数据
		// If the new font size is the same as the old font size, execution will be skipped and nothing will happen
		// After the function runs successfully, it will clear all generated font data
		void SetFontSize(float fontSize);

		float GetFontSize() const {
			return m_fontSize;
		}

		float GetLineHeight() const {
			return m_lineHeight;
		}

	private:
		float m_fontSize {};
		float m_lineHeight {};

		std::unordered_map<CharType, SCharacter *> m_characters {};

		FT_Library m_ftLib = nullptr;
		FT_Face m_ftFace = nullptr;

		// 对于 m_fontSize 非整数时，SCharacter 内的数据需要有一个缩放，就用这个值
		// For when m_fontSize is not an integer, the data in SCharacter needs to be scaled, so use this value
		float m_floatingScale {};

	public:
		inline static bool __IsWordChar(CharType character) {
			static std::unordered_set<CharType> __wordCharSet {
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
				'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
				'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				'~', '`', '!', '@', '#', '$', '%', '^', '&', '_', '=',
				'+', /* '-',*/ '*', '/', '<', '>', ',', '.', '?', '\'', '\"', '\\', '|',
				'(', ')', '[', ']', '{', '}'
			};
			static auto __end = __wordCharSet.end();
			return __wordCharSet.find(character) != __end;
		}

		// Sample of What_need_to_do_when_wrap:
		// [](size_t lineHeadIndex, size_t lineTailIndex, const Vec2 & vOffset_TopLeft_of_this_line, float width_of_this_line) { ... }
		void TextAutoWrapBase(UTF8StringView utf8Text, float _maxLineWidth, const std::function<void (size_t, size_t, const Vec2 &, float)> & What_need_to_do_when_wrap) {
			TextAutoWrapBase(UTF8Utils::ToUnicode(utf8Text), _maxLineWidth, What_need_to_do_when_wrap);
		}
		void TextAutoWrapBase(UnicodeStringView unicodeText, float _maxLineWidth, const std::function<void (size_t, size_t, const Vec2 &, float)> & What_need_to_do_when_wrap);

		float TextWidth(UTF8StringView utf8Text, float _maxLineWidth) {
			return TextWidth(UTF8Utils::ToUnicode(utf8Text), _maxLineWidth);
		}
		float TextHeight(UTF8StringView utf8Text, float _maxLineWidth) {
			return TextHeight(UTF8Utils::ToUnicode(utf8Text), _maxLineWidth);
		}
		Vec2 TextSize(UTF8StringView utf8Text, float _maxLineWidth) {
			return TextSize(UTF8Utils::ToUnicode(utf8Text), _maxLineWidth);
		}

		float TextWidth(UnicodeStringView unicodeText, float _maxLineWidth);
		float TextHeight(UnicodeStringView unicodeText, float _maxLineWidth);
		Vec2 TextSize(UnicodeStringView unicodeText, float _maxLineWidth);

		struct STextAutoWrapLineFormat {
			size_t headIndex;
			size_t tailIndex;
			Vec2 vOffset;
			float width;
		};
		std::vector<STextAutoWrapLineFormat> TextAutoWrapLineFormats(UTF8StringView utf8Text, float _maxLineWidth) {
			return TextAutoWrapLineFormats(UTF8Utils::ToUnicode(utf8Text), _maxLineWidth);
		}
		std::vector<STextAutoWrapLineFormat> TextAutoWrapLineFormats(UnicodeStringView unicodeText, float _maxLineWidth);

	};

}
