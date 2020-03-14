#include "JEpch.h"

#include "OpenGLShader.h"
#include "glad/glad.h"
#include "gtc/type_ptr.hpp"

namespace JEngine {

	bool checkStatus(
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

	bool checkShaderStatus(GLuint shaderID) {
		return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	}

	bool checkProgramStatus(GLuint programID) {
		return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	}

	OpenGLShader::OpenGLShader(const std::string& vertshader,const std::string& fragshader) {
		ProgramID = glCreateProgram();
		VertShaderID = glCreateShader(GL_VERTEX_SHADER);
		FragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		
		const GLchar* adapter[1];
		adapter[0] = vertshader.c_str();
		glShaderSource(VertShaderID, 1, adapter, 0);
		glCompileShader(VertShaderID);
		if (!checkShaderStatus(VertShaderID)) JE_CORE_ASSERT(false, "Can't Compile Shader");
		glAttachShader(ProgramID, VertShaderID);
		glLinkProgram(ProgramID);
		if (!checkProgramStatus(ProgramID)) JE_CORE_ASSERT(false, "Can't Attach Shader");

		adapter[0] = fragshader.c_str();
		glShaderSource(FragShaderID, 1, adapter, 0);
		glCompileShader(FragShaderID);
		if (!checkShaderStatus(FragShaderID)) JE_CORE_ASSERT(false, "Can't Compile Shader");
		glAttachShader(ProgramID, FragShaderID);
		glLinkProgram(ProgramID);
		if (!checkProgramStatus(ProgramID)) JE_CORE_ASSERT(false, "Can't Attach Shader");

	}

	void OpenGLShader::Bind() const {
		glUseProgram(ProgramID);
	}

	void OpenGLShader::UnBind() const {
		glUseProgram(0);
	}

	//----------------------------------SET VALUE PART-------------------------------------------//

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