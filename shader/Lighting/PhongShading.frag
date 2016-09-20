#version 440

in vec3 Position;
in vec3 Normal;

struct MaterialInfo 
{
	vec3 Kd;
	vec3 Ks;
	vec3 Ka;
    float Shininess;
};

struct LightInfo 
{
    vec4 Position;
    vec3 Intensity;
};

uniform LightInfo Light;
uniform MaterialInfo Material;

layout(location = 0) out vec4 FragColor;

vec3 ads()
{
    vec3 s = normalize( vec3(Light.Position) - Position );
    vec3 v = normalize( -Position );
    vec3 h = normalize( v + s );

    return Light.Intensity * (Material.Ka + Material.Kd * max(dot(s, Normal), 0.0));// + Material.Ks * pow(max(dot(h, Normal), 0.0), Material.Shininess));
}

void main()
{
    FragColor = vec4(ads(), 1.0);
}

