#type vertex
#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normal;

uniform mat4 TransformMatrix;
uniform mat4 FullMatrix;

out vec3 thePosition;
out vec3 theNormal;

out vec3 testColor;

void main()
{
	vec4 v = vec4(position,1.0);
	gl_Position = FullMatrix * v;
	thePosition = vec3(TransformMatrix * v);
	theNormal = normalize(vec3(TransformMatrix * vec4(normal,0)));
	testColor = normal;
}

#type fragment
#version 430

out vec4 daColor;

in vec3 thePosition;
in vec3 theNormal;

in vec3 testColor;

uniform vec3 CameraPosition;

uniform vec3 LightPosition;
uniform float AmbientLightScalar;
uniform float DiffuseLightScalar;
uniform float SpecularLightRadius;
uniform float SpecularLightPow;

void main()
{
	daColor = vec4(1.0,1.0,0.0,1.0);
}