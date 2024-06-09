#include <FrameAsset/Font.h>

#include <FrameAsset/Sprite.h>
#include <FrameCore/Log.h>
#include <FrameRender/RendererBase.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <glad/glad.h>

#include <iostream>

namespace Frame {

	CFont::SCharacter::SCharacter(unsigned int _textureId, const Vec2 & _size, const Vec2 & _bearing, const Vec2 & _advance)
		: textureId { _textureId }
		, size { _size }
		, bearing { _bearing }
		, advance { _advance }
		, vertexBuffer {
			_size.x, 0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 0.f, 0.f,
			_size.x, _size.y, 0.f, 1.f, 1.f,
			0.f, _size.y, 0.f, 0.f, 1.f
		}
	{
		glGenVertexArrays(1, & m_VAO);
		glGenBuffers(1, & m_VBO);

		RendererBase::BindVAO(m_VAO);

		RendererBase::BindVBO(m_VBO);

		GLsizei stride = (3 + 2) * (GLsizei)sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		RendererBase::BindVAO(0);
	}

	CFont::CFont(const char * filename, float fontSize) {
		FT_Error ftError = 0;

		ftError = FT_Init_FreeType(& m_ftLib);
		if(ftError) {
			Log::Log(Log::ELevel::Error, "Failed to initialize FreeType. Error code: %d", ftError);
			return;
		}

		ftError = FT_New_Face(m_ftLib, filename, 0, & m_ftFace);
		if(ftError) {
			Log::Log(Log::ELevel::Error, "Failed to create a new FreeType face. Error code: %d", ftError);
			return;
		}

		SetFontSize(fontSize);
	}

	CFont::~CFont() {
		DestroyAllCharacters();
		FT_Done_Face(m_ftFace);
		FT_Done_FreeType(m_ftLib);
	}

	CFont::SCharacter * CFont::InitializeCharacter(CharType _character) {
		DestroyCharacter(_character);
		
		FT_Error ftError = FT_Load_Char(m_ftFace, _character, FT_LOAD_RENDER);
		if(ftError) {
			Log::Log(Log::ELevel::Error, "Failed to load the character. Character ID: %d. Error code: %d", _character, ftError);
			return nullptr;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLuint texture;
		glGenTextures(1, & texture);
		RendererBase::BindTextureId(texture);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RED,
			m_ftFace->glyph->bitmap.width, m_ftFace->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, m_ftFace->glyph->bitmap.buffer
		);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		return m_characters[_character] = new SCharacter {
			texture,
			Vec2Cast(m_ftFace->glyph->bitmap.width, m_ftFace->glyph->bitmap.rows) * m_floatingScale,
			Vec2Cast(m_ftFace->glyph->bitmap_left, m_ftFace->glyph->bitmap_top) * m_floatingScale,
			Vec2Cast(m_ftFace->glyph->advance.x, m_ftFace->glyph->advance.y) / 64.f * m_floatingScale
		};
	}

	void CFont::DestroyCharacter(CharType _character) {
		auto it = m_characters.find(_character);
		if(it == m_characters.end()) {
			return;
		}
		glDeleteTextures(1, & it->second->textureId);
		delete it->second;
		m_characters.erase(it);
	}

	void CFont::DestroyAllCharacters() {
		for(auto & i : m_characters) {
			glDeleteTextures(1, & i.second->textureId);
			delete i.second;
		}
		m_characters.clear();
	}

	void CFont::SetFontSize(float fontSize) {
		if(fontSize == m_fontSize) {
			return;
		}

		DestroyAllCharacters();

		m_fontSize = fontSize;
		m_floatingScale = static_cast<float>(static_cast<int>(fontSize)) / fontSize;

		FT_F26Dot6 _charSize = static_cast<FT_F26Dot6>(fontSize);
		if(static_cast<float>(static_cast<int>(fontSize)) != fontSize) {
			_charSize += 1;
		}
		_charSize <<= 6;

		// TODO - 支持设定后两个参数的值
		FT_Set_Char_Size(m_ftFace, 0, _charSize, 0, 0);

		m_lineHeight = static_cast<float>(m_ftFace->size->metrics.height) / 64.f * m_floatingScale;
	}

	void CFont::TextAutoWrapBase(UnicodeStringView unicodeText, float _maxLineWidth, const std::function<void (size_t, size_t, const Vec2 &, float)> & What_need_to_do_when_wrap) {
		if(_maxLineWidth <= 0.f) {
			_maxLineWidth = FLT_MAX;
		}

		// 这三个变量名开头的 i 意思是 index，也就是下方 for 循环里的 i
		// The "i" at the beginning of these three variable names means "index", which is the "i" in the for loop below
		constexpr size_t iInvalid = SIZE_MAX; size_t iLineHead = 0, iLineTail = iInvalid;

		Vec2 vLineOff { 0.f };

		// currLineWidth: 每个遍历到的字符的宽度都会计入
		// currLineWidthApplied: 表示每行最终得出的实际宽度
		// currLineWidth: The width of each traversed character will be included in the calculation
		// currLineWidthApplied: represents the actual width ultimately obtained for each row
		float currLineWidth = 0.f, currLineWidthApplied = 0.f;

		bool bThisLineIsAlreadyHaveANotWordChar = false;

#define __TEXTAUTOWRAPBASE_NEXTLINE \
	What_need_to_do_when_wrap(iLineHead, iLineTail, vLineOff, currLineWidthApplied); \
	vLineOff.y += m_lineHeight; \
	currLineWidth = 0.f;

		size_t len = unicodeText.length();
		for(size_t i = 0; i < len; i++) {
			CFont::CharType character = unicodeText[i];

			if(character == '\n') {
				iLineTail = i - 1;
				currLineWidthApplied = currLineWidth;
				__TEXTAUTOWRAPBASE_NEXTLINE;
				iLineHead = i + 1;
				continue;
			}

			CFont::SCharacter * pCharacter = GetOrInitCharacter(character);

			bool bCurrentIsNotWordChar = !__IsWordChar(character);

			currLineWidth += pCharacter->advance.x;
			if(currLineWidth <= _maxLineWidth) {
				if(bCurrentIsNotWordChar) {
					iLineTail = i;
					currLineWidthApplied = currLineWidth;
					bThisLineIsAlreadyHaveANotWordChar = true;
				}
			} else {
				if(bCurrentIsNotWordChar || bThisLineIsAlreadyHaveANotWordChar) {
					// 下一行 | Next Line

					if(iLineTail < iLineHead || iLineTail == iInvalid) {
						iLineTail = i;
						currLineWidthApplied = currLineWidth;
					}
					else if(character == ' ') {
						iLineTail = i;
						currLineWidth -= pCharacter->advance.x;
						currLineWidthApplied = currLineWidth;
					} else {
						currLineWidth -= pCharacter->advance.x;
					}

					__TEXTAUTOWRAPBASE_NEXTLINE;
					i = iLineTail;
					iLineHead = i + 1;

					bThisLineIsAlreadyHaveANotWordChar = false;
				}
			}
		}

#undef __TEXTAUTOWRAPBASE_NEXTLINE

		What_need_to_do_when_wrap(iLineHead, len - 1, vLineOff, currLineWidth);

		return;
	}

	float CFont::TextWidth(UnicodeStringView unicodeText, float _maxLineWidth) {
		float result = 0.f;
		TextAutoWrapBase(unicodeText, _maxLineWidth,
			[& result](size_t, size_t, const Vec2 &, float _width) {
				if(_width > result) {
					result = _width;
				}
			}
		);
		return result;
	}

	float CFont::TextHeight(UnicodeStringView unicodeText, float _maxLineWidth) {
		float result = 0.f;
		TextAutoWrapBase(unicodeText, _maxLineWidth,
			[& result](size_t, size_t, const Vec2 & _vOffset, float) {
				result = _vOffset.y;
			}
		);
		return result + m_lineHeight;
	}

	Vec2 CFont::TextSize(UnicodeStringView unicodeText, float _maxLineWidth) {
		float resultWidth = 0.f, resultHeight = 0.f;
		TextAutoWrapBase(unicodeText, _maxLineWidth,
			[& resultWidth, & resultHeight](size_t, size_t, const Vec2 & _vOffset, float _width) {
				if(_width > resultWidth) {
					resultWidth = _width;
				}
				resultHeight = _vOffset.y;
			}
		);
		return { resultWidth, resultHeight + m_lineHeight };
	}

	std::vector<CFont::STextAutoWrapLineFormat> CFont::TextAutoWrapLineFormats(UnicodeStringView unicodeText, float _maxLineWidth) {
		std::vector<STextAutoWrapLineFormat> result {};

		TextAutoWrapBase(unicodeText, _maxLineWidth,
			[& result](auto a, auto b, auto c, auto d) {
				result.push_back({ a, b, c, d });
			}
		);

		return result;
	}
	
}