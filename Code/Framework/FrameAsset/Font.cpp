﻿#include <FrameAsset/Font.h>

#include <FrameAsset/Sprite.h>

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

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		GLsizei stride = (3 + 2) * (GLsizei)sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	CFont::CFont(const char * filename, float fontSize) {
		FT_Error ftError = 0;

		ftError = FT_Init_FreeType(& m_ftLib);
		if(ftError) {
			printf("[ERROR] %d %d\n", ftError, __LINE__); // TODO
			return;
		}

		ftError = FT_New_Face(m_ftLib, filename, 0, & m_ftFace);
		if(ftError) {
			printf("[ERROR] %d %d\n", ftError, __LINE__); // TODO
			return;
		}

		SetFontSize(fontSize);

		for(CharType i = 0; i < 128; i++) {
			InitializeCharacter(i);
		}
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
			printf("[ERROR] %d %d\n", ftError, __LINE__); // TODO
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