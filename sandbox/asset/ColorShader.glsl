#type vertex
#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normal;

uniform mat4 TransformMatrix;
uniform mat4 CameraMatrix;
uniform mat4 ProjectionMatrix;

out vec3 thePosition;
out vec3 theNormal;

out vec3 theColor;

void main()
{
	vec4 v = vec4(position,1.0);
	gl_Position = ProjectionMatrix * CameraMatrix * TransformMatrix * v;
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

struct LightStruct{
	vec3 Position;
	float Ambient;
	float Diffuse;
	float Radius;
	float Pow;
	bool isAbled;
};

uniform LightStruct Light[10];
uniform int LightNum;
void main()
{
	float finalBrightness = 0.0;
	for(int i = 0;i < 10; i++)
		if(Light[i].isAbled){
		//diffuse light
		vec3 lightVector = normalize(Light[i].Position - thePosition);
		float brightness = Light[i].Diffuse * dot(theNormal,lightVector);

		//specular Light
		vec3 reflectedLightVector = reflect(-lightVector,theNormal);
		vec3 CameraVector = normalize(CameraPosition - thePosition);
		float specularity = clamp(dot(reflectedLightVector,CameraVector),0,1);

		//Specular Light Attenuation
		float r = Light[i].Radius, d = length(Light[i].Position - thePosition);
		float kc = 1, kl = 2.0/r, kq = 1.0/(r*r);
		float attenuation = 1.0 / (kc + kl * d + kq * d * d);

		specularity = attenuation * pow(specularity,Light[i].Pow);

		float specularLight = 0;
		if(dot(lightVector,theNormal) > 0)
			specularLight = specularity;

		finalBrightness += Light[i].Ambient + attenuation * max(0,brightness) + attenuation * specularLight;
	}
	vec3 f = vec3(finalBrightness);
	vec3 test =  min(theColor.rgb * f,vec3(1.0));
	daColor = vec4(test,1.0);
}