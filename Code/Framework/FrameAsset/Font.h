#pragma once

#include <FrameCore/BasicTypes.h>
#include <FrameMath/Vector2.h>

#include <unordered_map>

struct FT_LibraryRec_;
typedef FT_LibraryRec_ * FT_Library;

struct FT_FaceRec_;
typedef FT_FaceRec_ * FT_Face;

namespace Frame {

	class CFont {

	public:
		// Unicode
		typedef uint16 CharType;

		struct SCharacter {
			SCharacter() = default;
			SCharacter(unsigned int _textureId, unsigned int _w, unsigned int _h, int _bearingX, int _bearingY, int _advanceX, int _advanceY)
				: textureId { _textureId }
				, size { _w, _h }
				, bearing { _bearingX, _bearingY }
				, advance { _advanceX, _advanceY }
			{}

			unsigned int textureId = 0;
			Vec2_tpl<unsigned int> size {};
			Vec2i bearing {};
			Vec2i advance {};
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

	private:
		std::unordered_map<CharType, SCharacter *> m_characters {};

		FT_Library m_ftLib = nullptr;
		FT_Face m_ftFace = nullptr;
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
