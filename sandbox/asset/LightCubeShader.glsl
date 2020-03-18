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
	daColor = vec4(theColor,1.0);
}