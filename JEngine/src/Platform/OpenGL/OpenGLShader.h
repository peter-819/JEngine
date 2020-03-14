#include "JEpch.h"
#include "JEngine/Renderer/Shader.h"
#include "glad/glad.h"
#include "glm.hpp"

namespace JEngine {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertshader, const std::string& fragshader);
		virtual void Bind() const override;
		virtual void UnBind() const override;
		
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override; 
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		void UpLoadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UpLoadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

		
	private:
		GLuint FragShaderID;
		GLuint VertShaderID;
		GLuint ProgramID;
	};
}