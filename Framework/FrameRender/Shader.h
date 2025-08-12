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
	};

}