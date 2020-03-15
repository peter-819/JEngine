#include "JEpch.h"

#include "OpenGLShader.h"
#include "glad/glad.h"
#include "gtc/type_ptr.hpp"

namespace JEngine {
	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		JE_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	bool OpenGLShader::checkStatus(
		GLuint objectID,
		PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
		GLenum statusType
	) {
		GLint compileStatus;
		objectPropertyGetterFunc(objectID, statusType, &compileStatus);
		if (compileStatus != GL_TRUE) {
			GLint infoLogLength;
			objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* buffer = new GLchar[infoLogLength];
			GLsizei bufferSize;
			getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
			JE_CORE_ERROR("{0}", buffer);
			delete[] buffer;
			return false;
		}
		return true;
	}

	bool OpenGLShader::checkShaderStatus(GLuint shaderID) {
		return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	}

	bool OpenGLShader::checkProgramStatus(GLuint programID) {
		return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	}

	std::string OpenGLShader::ReadSource(const std::string & filepath) {
		std::ifstream meInput(filepath);
		if (!meInput.good()) {
			JE_CORE_ASSERT(false, "Failed to load shader file");
			exit(1);
		}
		return std::string(
			std::istreambuf_iterator<char>(meInput),
			std::istreambuf_iterator<char>()
		);
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSource) {
		ProgramID = glCreateProgram();
		for (auto& kv : ShaderSource) {
			GLuint ShaderID = glCreateShader(kv.first);
			
			const GLchar* adapter[1];
			adapter[0] = kv.second.c_str();
			glShaderSource(ShaderID, 1, adapter, 0);
			glCompileShader(ShaderID);
			JE_CORE_ASSERT(checkShaderStatus(ShaderID), "Can't compile shader");
			glAttachShader(ProgramID, ShaderID);
			glLinkProgram(ProgramID);
			JE_CORE_ASSERT(checkProgramStatus(ProgramID), "Can't Attach shader");
			glDeleteShader(ShaderID);
		}
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shadersource;

		const char* typetoken = "#type";
		size_t typeTokenLength = strlen(typetoken);
		size_t pos = source.find(typetoken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			JE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			JE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type");

			size_t NextLinePos = source.find_first_not_of("\r\n", eol);
			JE_CORE_ASSERT(NextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typetoken, NextLinePos);

			shadersource[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(NextLinePos) : source.substr(NextLinePos, pos - NextLinePos);
		}
		return shadersource;
	}

	OpenGLShader::OpenGLShader(const std::string& vertshader,const std::string& fragshader) {
		std::unordered_map<GLenum, std::string> ShaderSource;
		ShaderSource[GL_VERTEX_SHADER] = vertshader;
		ShaderSource[GL_FRAGMENT_SHADER] = fragshader;
		Compile(ShaderSource);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) {
		std::string source = ReadSource(filepath);
		auto shadersources = PreProcess(source);
		Compile(shadersources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(ProgramID);
	}

	void OpenGLShader::UnBind() const {
		glUseProgram(0);
	}

	const std::string& OpenGLShader::GetName() const { return m_Name; }
	//----------------------------------SET VALUE PART-------------------------------------------//

	void OpenGLShader::SetFloat (const std::string& name, float value) {
		UpLoadUniformFloat (name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value) {
		UpLoadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
		UpLoadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) {
		UpLoadUniformFloat4(name, value);
	}	 
	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix) {
		UpLoadUniformMat3(name, matrix);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix) {
		UpLoadUniformMat4(name, matrix);
	}

	//-------------------------------UPLOAD UNIFORM VALUE PART------------------------------------//
	void OpenGLShader::UpLoadUniformFloat (const std::string& name, float value) {
		GLuint location = glGetUniformLocation(ProgramID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UpLoadUniformFloat2(const std::string& name, const glm::vec2& value) {
		GLuint location = glGetUniformLocation(ProgramID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UpLoadUniformFloat3(const std::string& name, const glm::vec3& value) {
		GLuint location = glGetUniformLocation(ProgramID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UpLoadUniformFloat4(const std::string& name, const glm::vec4& value) {
		GLuint location = glGetUniformLocation(ProgramID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
		
	void OpenGLShader::UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(ProgramID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	
	void OpenGLShader::UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(ProgramID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}