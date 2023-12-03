#pragma once

#include <FrameCore/BasicTypes.h>
#include <FrameMath/Vector2.h>

#include <unordered_map>

struct FT_LibraryRec_;
typedef FT_LibraryRec_ * FT_Library;

struct FT_FaceRec_;
typedef FT_FaceRec_ * FT_Face;

namespace Frame {

	class CStaticSprite;

	class CFont {

	public:
		// Unicode
		typedef UnicodeChar CharType;

		struct SCharacter {
			SCharacter() = default;
			SCharacter(unsigned int _textureId, const Vec2 & _size, const Vec2 & _bearing, const Vec2 & _advance)
				: textureId { _textureId }
				, size { _size }
				, bearing { _bearing }
				, advance { _advance }
			{}

			unsigned int textureId = 0;
			Vec2 size {};
			Vec2 bearing {};
			Vec2 advance {};
		};

	public:

		CFont() = delete;
		CFont(const char * filename, float fontSize);
		virtual ~CFont();

		SCharacter * InitializeCharacter(CharType _character);
		
		void DestroyCharacter(CharType _character);

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

	public:
		float m_fontSize;
		float m_lineHeight;

	private:
		std::unordered_map<CharType, SCharacter *> m_characters {};

		FT_Library m_ftLib = nullptr;
		FT_Face m_ftFace = nullptr;

		// 对于 m_fontSize 非整数时，SCharacter 内的数据需要有一个缩放，就用这个值
		// For when m_fontSize is not an integer, the data in SCharacter needs to be scaled, so use this value
		float m_floatingScale;
	};

	/*

	class CFont {
	public:
		CFont() = delete;
		CFont(const char * filename, int fontSize);
		virtual ~CFont();

		enum class EHAlign {
			Left = 0,
			Center = 1,
			Right = 2
		};
		enum class EVAlign {
			Top = 0,
			Middle = 1,
			Bottom = 2
		};

		typedef EHAlign EWrappedAlign;

		TTF_Font * GetSdlFont() const { return m_font; }

		void SetSize(int size);
		int GetSize() const { return m_size; }

		void SetWrappedAlign(EWrappedAlign wrappedAlign);

		EWrappedAlign GetWrappedAlign() const { return m_wrappedAlign; }

		void SetAlign(EHAlign hAlign, EVAlign vAlign, bool bAlsoSetWrappedAlign = true) {
			SetHAlign(hAlign, bAlsoSetWrappedAlign);
			SetVAlign(vAlign);
		}
		void SetHAlign(EHAlign hAlign, bool bAlsoSetWrappedAlign = true) {
			m_hAlign = hAlign;
			if(bAlsoSetWrappedAlign) {
				SetWrappedAlign(hAlign);
			}
		}
		void SetVAlign(EVAlign vAlign) { m_vAlign = vAlign; }

		EHAlign GetHAlign() const { return m_hAlign; }
		EVAlign GetVAlign() const { return m_vAlign; }

	private:
		TTF_Font * m_font = nullptr;
		int m_size = 0;
		EHAlign m_hAlign = EHAlign::Left;
		EVAlign m_vAlign = EVAlign::Top;
		EWrappedAlign m_wrappedAlign {};
	};
	*/
}
