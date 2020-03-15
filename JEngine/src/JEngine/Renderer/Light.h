#pragma once
#include "glm.hpp"
#include "JEngine/Renderer/Shader.h"

namespace JEngine {
	class Light {
	//private:
	public:					//TODO: For Debug
		glm::vec3 LightPosition;
		float AmbientLightScalar;
		float DiffuseLightScalar;
		float SpecularLightRadius;
		float SpecularLightPow;

	public:
		Light() {}
		~Light() {}
		void setLight(
			glm::vec3 LightPosition,
			float AmbientLightScalar,
			float DiffuseLightScalar,
			float SpecularLightRadius,
			float SpecularLightPow
		);
		void BindShader(Ref<Shader> shader);
		glm::vec3 getLightPosition();
	};
}