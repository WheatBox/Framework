#include <FrameAsset/Font.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <glad/glad.h>

#include <iostream>

namespace Frame {

	CFont::CFont(const char * filename, float fontSize)
		: m_fontSize { fontSize }
	{
		FT_Error ftError = 0;

		ftError = FT_Init_FreeType(& m_ftLib);
		if(ftError) {
			printf("[ERROR] %d\n", ftError); // TODO
			return;
		}

		ftError = FT_New_Face(m_ftLib, filename, 0, & m_ftFace);
		if(ftError) {
			printf("[ERROR] %d\n", ftError); // TODO
			return;
		}

		// TODO - 支持设定后两个参数的值
		FT_Set_Char_Size(m_ftFace, 0, static_cast<FT_F26Dot6>(fontSize * 64.f), 72, 72);

		for(CharType i = 0; i < 128; i++) {
			InitializeCharacter(i);
		}
	}

	CFont::~CFont() {
		for(auto & i : m_characters) {
			DestroyCharacter(i.first);
		}
		FT_Done_Face(m_ftFace);
		FT_Done_FreeType(m_ftLib);
	}

	CFont::SCharacter * CFont::InitializeCharacter(CharType _character) {
		DestroyCharacter(_character);
		
		FT_Error ftError = FT_Load_Char(m_ftFace, _character, FT_LOAD_RENDER);
		if(ftError) {
			printf("[ERROR] %d\n", ftError); // TODO
			return nullptr;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLuint texture;
		glGenTextures(1, & texture);
		glBindTexture(GL_TEXTURE_2D, texture);
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
			m_ftFace->glyph->bitmap.width, m_ftFace->glyph->bitmap.rows,
			m_ftFace->glyph->bitmap_left, m_ftFace->glyph->bitmap_top,
			m_ftFace->glyph->advance.x, m_ftFace->glyph->advance.y
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

}

#if 0
#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Frame {

	CFont::CFont(const char * filename, int fontSize) {
		m_size = fontSize;
		m_font = TTF_OpenFont(filename, fontSize);

		SetWrappedAlign(EWrappedAlign::Left);
	}

	CFont::~CFont() {
		TTF_CloseFont(m_font);
	}

	void CFont::SetSize(int size) {
		m_size = size;
		TTF_SetFontSize(m_font, size);
	}

	void CFont::SetWrappedAlign(EWrappedAlign wrappedAlign) {
		TTF_SetFontWrappedAlign(m_font, static_cast<int>(wrappedAlign));
	}

}
#endif