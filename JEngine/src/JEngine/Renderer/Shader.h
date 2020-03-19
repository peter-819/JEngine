#pragma once
#include "JEpch.h"
#include "glm.hpp"

namespace JEngine {
	class Shader {
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& name,const std::string& vertshader, const std::string& fragshader);
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		
		virtual void SetFloat (const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;		
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
																	   
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void SetBool(const std::string& name, bool value) = 0;

	};

	class ShaderLibrary {
	public:
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		
		Ref<Shader> Get(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}