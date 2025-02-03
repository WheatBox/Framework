#pragma once

namespace Frame {

	class CShader {
	private:
		unsigned int m_glProgramId = 0;

	public:
		CShader() = default;
		virtual ~CShader() = default;

		unsigned int GetGlProgramId() const {
			return m_glProgramId;
		}

		bool Compile(const char * szVertexShaderCode, const char * szFragmentShaderCode);
		bool CompileFiles(const char * szVertexShaderPath, const char * szFragmentShaderPath);
		void Destroy();

		void Use() const;

		void SetUniformInt(const char * szUniformName, int value);
		void SetUniformFloat(const char * szUniformName, float value);
		
		void SetUniformVec2(const char * szUniformName, const float * values) {
			SetUniformVec2(szUniformName, values[0], values[1]);
		}
		void SetUniformVec2(const char * szUniformName, float value0, float value1);

		void SetUniformVec3(const char * szUniformName, const float * values) {
			SetUniformVec3(szUniformName, values[0], values[1], values[2]);
		}
		void SetUniformVec3(const char * szUniformName, float value0, float value1, float value2);

		void SetUniformVec4(const char * szUniformName, const float * values) {
			SetUniformVec4(szUniformName, values[0], values[1], values[2], values[3]);
		}
		void SetUniformVec4(const char * szUniformName, float value0, float value1, float value2, float value3);

		void SetUniformMat3(const char * szUniformName, const float * values);

		void SetUniformMat4(const char * szUniformName, const float * values);

	};

}