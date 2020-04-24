#type vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;
in layout(location = 2) vec3 normal;

uniform mat4 TransformMatrix;
uniform mat4 CameraMatrix;
uniform mat4 ProjectionMatrix;

out vec3 thePosition;
out vec3 theColor;
out vec3 theNormal;

void main(){
    vec4 v = vec4(position, 1.0);
    gl_Position = ProjectionMatrix * CameraMatrix * TransformMatrix * v;
    thePosition = vec3(TransformMatrix * v);
    theNormal = normalize(vec3(TransformMatrix * vec4(normal,0)));
    theColor = color;
}

#type fragment
#version 430

out vec4 daColor;

in vec3 thePosition;
in vec3 theColor;
in vec3 theNormal;

struct LightProperties {
    bool isEnabled;
    bool isLocal;
    bool isSpot;

    vec3 position;
    vec3 color;

    vec3 coneDirection;
    float spotCosCutoff;
    float spotExponent;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

struct MaterialProperties {
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

const int MaxLights = 10;
uniform LightProperties Lights[MaxLights];
uniform MaterialProperties Material;

uniform CameraPosition;

void main() {
    vec3 scatteredLight = vec3(0.0);
    vec3 reflectedLight = vec3(0.0);

    for(int i=0; i<MaxLights; i++){
        if(!Lights[i].isEnabled) continue;

        vec3 halfVector;
        vec3 lightDirection = Lights[i].position;
        float attenuation = 1.0;
        if(Lights[i].isLocal){
            lightDirection = lightDirection - vec3(thePosition);
            float lightDistance = length(lightDirection);
            lightDirection = lightDirection / lightDistance;

            attenuation = 1.0 / (Lights[i].constantAttenuation
                                +Lights[i].linearAttenuation * lightDistance
                                +Lights[i].quadraticAttenuation * lightDistance * lightDistance);
            if(Lights[i].isSpot){
                float spotCos = dot(lightDirection,-Lights[i].coneDirection);
                if(spotCos < Lights[i].spotCosCutoff)
                    attenuation = 0.0;
                else
                    attenuation *= pow(spotCos,Lights[i].spotExponent);
            }
            halfVector = normalize(lightDirection + CameraPosition);
        }
        else { halfVector = Lights[i].halfVector; }

        float diffuse = max(0.0,dot(theNormal,lightDirection));
        float specular = max(0.0,dot(theNormal,halfVector));

        if(diffuse == 0.0) specular = 0.0;
        else specular = pow(specular,shininess) * Strength;

        scatteredLight += Material.ambient * Material.ambient * attenuation +
                            Lights[i].color * Material.specular * diffuse * attenuation;

        reflectedLight += Lights[i].color * specular * attenuation;
    }
    vec3 rgb = min(Material.emission + Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    daColor = rgb;
}