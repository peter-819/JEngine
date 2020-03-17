#type vertex
#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normal;

uniform mat4 TransformMatrix;
uniform mat4 FullMatrix;

out vec3 thePosition;
out vec3 theNormal;

out vec3 theColor;

void main()
{
	vec4 v = vec4(position,1.0);
	gl_Position = FullMatrix * v;
	thePosition = vec3(TransformMatrix * v);
	theNormal = normalize(vec3(TransformMatrix * vec4(normal,0)));
	theColor = vertexColor;
}

#type fragment
#version 430

out vec4 daColor;

in vec3 thePosition;
in vec3 theNormal;

in vec3 theColor;

uniform vec3 CameraPosition;

uniform vec3 LightPosition;
uniform float AmbientLightScalar;
uniform float DiffuseLightScalar;
uniform float SpecularLightRadius;
uniform float SpecularLightPow;

void main()
{
	//diffuse light
	vec3 lightVector = normalize(LightPosition - thePosition);
	float brightness = DiffuseLightScalar * dot(theNormal,lightVector);

	//specular Light
	vec3 reflectedLightVector = reflect(-lightVector,theNormal);
	vec3 CameraVector = normalize(CameraPosition - thePosition);
	float specularity = clamp(dot(reflectedLightVector,CameraVector),0,1);
	
	//Specular Light Attenuation
	float r = SpecularLightRadius, d = length(LightPosition - thePosition);
	float kc = 1, kl = 2.0/r, kq = 1.0/(r*r);
	float attenuation = 1.0 / (kc + kl * d + kq * d * d);
	
	specularity = attenuation* pow(specularity,SpecularLightPow);

	float specularLight = 0;
	if(dot(lightVector,theNormal) > 0)
		specularLight = specularity;

	float finalBrightness = AmbientLightScalar + brightness + specularity;
	//float f = clamp(finalBrightness,0,1);
	//daColor = vec4(f,f,f,1);
	vec3 f = vec3(finalBrightness);
	vec3 test =  min(theColor.rgb * f,vec3(1.0));
	daColor = vec4(test,1.0);
	//daColor = vec4(test,1.0);
}