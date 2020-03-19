#include "JEpch.h"
#include "JEngine/Renderer/Shader.h"
#include "glad/glad.h"
#include "glm.hpp"

namespace JEngine {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertshader, const std::string& fragshader);
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& filepath);

		virtual void Bind() const override;
		virtual void UnBind() const override;
		
		virtual const std::string& GetName() const override;

		virtual void SetFloat (const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual void SetBool(const std::string& name, bool value) override;

		void UpLoadUniformFloat (const std::string& name, float value);
		void UpLoadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UpLoadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UpLoadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void UpLoadUniformBool(const std::string& name, bool value);

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSource);
		std::string ReadSource(const std::string& filepath);
		bool checkStatus(
			GLuint objectID,
			PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
			PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
			GLenum statusType
		);
		bool checkShaderStatus(GLuint shaderID);
		bool checkProgramStatus(GLuint programID);
	
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string m_Name;
		GLuint ProgramID;
	};
}