#include "JEpch.h"
#include "Light.h"

namespace JEngine {
	void Light::setLight(
		glm::vec3 LightPosition,
		float AmbientLightScalar,
		float DiffuseLightScalar,
		float SpecularLightRadius,
		float SpecularLightPow
	) {
		this->LightPosition = LightPosition,
		this->AmbientLightScalar = AmbientLightScalar,
		this->DiffuseLightScalar = DiffuseLightScalar,
		this->SpecularLightRadius = SpecularLightRadius,
		this->SpecularLightPow = SpecularLightPow;
	}

	void Light::BindShader(Ref<Shader> shader) {

	}
}