#version 400

in vec3 Position;
in vec3 Normal;

struct LightInfo {
    vec4 position;
    vec3 intensity;
    float shininess;
};
uniform LightInfo Light;

uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ka;
uniform float Shininess;

layout(location = 0) out vec4 FragColor;

vec3 ads(){
vec3 n = normalize(Normal);
vec3 v = normalize(-Position);
vec3 s = normalize(vec3(Light.position) - Position);
vec3 r = reflect(-s, n);
vec3 h = normalize(v+s);
return Light.intensity * (Ka + Kd*max(dot(s, n), 0.0) + Ks*pow(max(dot(r, v), 0.0), Light.shininess));
//return LightIntensity * (Ka + Kd*max(dot(s, n), 0.0)+ Ks*pow(max(dot(h, n), 0.0), Shininess));
}

void main(){
FragColor = vec4(ads(), 1.0);
}