#include "Shader.h"

#include "../FrameCore/Globals.h"
#include "../FrameCore/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#define INFOLOG_START \
	int len = 0; \
	glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, & len); \
	char * infoLog = (char *)malloc(sizeof(char) * (len + 1)); \
	glGetShaderInfoLog(vertex, len + 1, NULL, infoLog);

#define INFOLOG_END \
	free(infoLog); \
	infoLog = nullptr;

namespace Frame {

	bool CShader::Compile(const char * szVertexShaderCode, const char * szFragmentShaderCode) {
		int success;

		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, & szVertexShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, & success);
		if(!success) {
			INFOLOG_START;
			Log::Log(Log::ELevel::Error, "Failed to compile the vertex shader. Detail: %s", infoLog);
			INFOLOG_END;

			glDeleteShader(vertex);
			return false;
		}

		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, & szFragmentShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, & success);
		if(!success) {
			INFOLOG_START;
			Log::Log(Log::ELevel::Error, "Failed to compile the fragment shader. Detail: %s", infoLog);
			INFOLOG_END;

			glDeleteShader(fragment);
			return false;
		}

		m_glProgramId = glad_glCreateProgram();
		glAttachShader(m_glProgramId, vertex);
		glAttachShader(m_glProgramId, fragment);
		glLinkProgram(m_glProgramId);

		glGetProgramiv(m_glProgramId, GL_LINK_STATUS, & success);
		if(!success) {
			INFOLOG_START;
			Log::Log(Log::ELevel::Error, "Failed to create shader programs. Detail: %s", infoLog);
			INFOLOG_END;

			glDeleteProgram(m_glProgramId);
			return false;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return true;
	}

	bool CShader::CompileFiles(const char * szVertexShaderPath, const char * szFragmentShaderPath) {

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertShaderFile;
		std::ifstream fragShaderFile;

		vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vertShaderFile.open(szVertexShaderPath);
			fragShaderFile.open(szFragmentShaderPath);

			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vertShaderFile.rdbuf();
			fShaderStream << fragShaderFile.rdbuf();

			vertShaderFile.close();
			fragShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		} catch(std::ifstream::failure & e) {
			Log::Log(Log::ELevel::Error, "Failed to load shaders. Detail: %s", e.what());
			return false;
		}

		return Compile(vertexCode.c_str(), fragmentCode.c_str());
	}

	void CShader::Destroy() {
		glDeleteProgram(m_glProgramId);
		m_glProgramId = 0;
	}

	void CShader::Use() const {
		if(gShaderInUsing != this) {
			gShaderInUsing = const_cast<CShader *>(this);
			glUseProgram(m_glProgramId);
		}
	}

	void CShader::SetUniformInt(const char * szUniformName, int value) const {
		glUniform1i(glGetUniformLocation(m_glProgramId, szUniformName), value);
	}

	void CShader::SetUniformFloat(const char * szUniformName, float value) const {
		glUniform1f(glGetUniformLocation(m_glProgramId, szUniformName), value);
	}

	void CShader::SetUniformVec2(const char * szUniformName, float value0, float value1) const {
		glUniform2f(glGetUniformLocation(m_glProgramId, szUniformName), value0, value1);
	}

	void CShader::SetUniformVec3(const char * szUniformName, float value0, float value1, float value2) const {
		glUniform3f(glGetUniformLocation(m_glProgramId, szUniformName), value0, value1, value2);
	}

	void CShader::SetUniformVec4(const char * szUniformName, float value0, float value1, float value2, float value3) const {
		glUniform4f(glGetUniformLocation(m_glProgramId, szUniformName), value0, value1, value2, value3);
	}

	void CShader::SetUniformMat3(const char * szUniformName, const float * values) const {
		glUniformMatrix3fv(glGetUniformLocation(m_glProgramId, szUniformName), 1, GL_FALSE, values);
	}

	void CShader::SetUniformMat4(const char * szUniformName, const float * values) const {
		glUniformMatrix4fv(glGetUniformLocation(m_glProgramId, szUniformName), 1, GL_FALSE, values);
	}
	
}
