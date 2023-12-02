#include <FrameRender/Shader.h>

#include <FrameCore/Globals.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace Frame {

	bool CShader::Compile(const char * szVertexShaderCode, const char * szFragmentShaderCode) {
		int success;
		char infoLog[512];

		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, & szVertexShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, & success);
		if(!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			printf("[ERROR] %s\n", infoLog); // TODO - 等Log系统做完后重写这一句（还有下面类似的句子）

			glDeleteShader(vertex);
			return false;
		}

		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, & szFragmentShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, & success);
		if(!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			printf("[ERROR] %s\n", infoLog);

			glDeleteShader(fragment);
			return false;
		}

		m_glProgramId = glad_glCreateProgram();
		glAttachShader(m_glProgramId, vertex);
		glAttachShader(m_glProgramId, fragment);
		glLinkProgram(m_glProgramId);

		glGetProgramiv(m_glProgramId, GL_LINK_STATUS, & success);
		if(!success) {
			glGetProgramInfoLog(m_glProgramId, 512, NULL, infoLog);
			printf("[ERROR] %s\n", infoLog);

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

		} catch(std::ifstream::failure e) {
			printf("[ERROR] %s\n", e.what());

			return false;
		}

		return Compile(vertexCode.c_str(), fragmentCode.c_str());
	}

	void CShader::Destroy() {
		glDeleteProgram(m_glProgramId);
	}

	void CShader::Use() const {
		if(gShaderInUsing != this) {
			gShaderInUsing = const_cast<CShader *>(this);
			glUseProgram(m_glProgramId);
		}
	}

	void CShader::SetUniformInt(const char * szUniformName, int value) {
		glUniform1i(glGetUniformLocation(m_glProgramId, szUniformName), value);
	}

	void CShader::SetUniformFloat(const char * szUniformName, float value) {
		glUniform1f(glGetUniformLocation(m_glProgramId, szUniformName), value);
	}

	void CShader::SetUniformVec2(const char * szUniformName, float value0, float value1) {
		glUniform2f(glGetUniformLocation(m_glProgramId, szUniformName), value0, value1);
	}

	void CShader::SetUniformVec3(const char * szUniformName, float value0, float value1, float value2) {
		glUniform3f(glGetUniformLocation(m_glProgramId, szUniformName), value0, value1, value2);
	}

	void CShader::SetUniformVec4(const char * szUniformName, float value0, float value1, float value2, float value3) {
		glUniform4f(glGetUniformLocation(m_glProgramId, szUniformName), value0, value1, value2, value3);
	}

	void CShader::SetUniformMat3(const char * szUniformName, const float * values) {
		glUniformMatrix3fv(glGetUniformLocation(m_glProgramId, szUniformName), 1, GL_FALSE, values);
	}

	void CShader::SetUniformMat4(const char * szUniformName, const float * values) {
		glUniformMatrix4fv(glGetUniformLocation(m_glProgramId, szUniformName), 1, GL_FALSE, values);
	}
	
}