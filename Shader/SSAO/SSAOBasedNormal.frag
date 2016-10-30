#version 400

struct LightInfo {
  vec4 Position;
  vec3 Intensity;
};

struct MaterialInfo {
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
  float Shininess;
};

uniform LightInfo Light;
uniform MaterialInfo Material;
uniform mat4 MVP;
uniform mat4 ProjectionMatrix;


uniform sampler2D PositionMap, NormalMap, AlbedoMap, DepthMap;
uniform sampler2D SampleMap;
uniform vec2 Viewport;

uniform int NumSamples;
uniform float SampleRadius;
uniform float Time;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;
layout (location = 3) out vec3 ColorData;

vec3 phongModel(vec3 pos, vec3 norm, vec3 albedo)
{
  vec3 n = norm;
  if( !gl_FrontFacing )
    n = -n;

  vec3 s = normalize(vec3(Light.Position) - pos);
  vec3 v = normalize(-pos);
  vec3 r = reflect( -s, n );
  float sDotN = max( dot(s, n), 0.0 );

  vec3 diffuse = Light.Intensity * albedo * sDotN;

  vec3 spec = Light.Intensity * Material.Ks *
    pow( max( dot(r, v), 0.0 ), Material.Shininess );

  return diffuse;// + spec;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;
subroutine (RenderPassType)
void renderGBuffer()
{
  PositionData = Position;
  NormalData = Normal;
  ColorData = Material.Kd;
}

subroutine (RenderPassType)
void render()
{
  vec3 pos    = vec3(texture(PositionMap, TexCoord));
  vec3 normal = vec3(texture(NormalMap, TexCoord));
  vec3 albedo = vec3(texture(AlbedoMap, TexCoord));

  vec3 ambient = Light.Intensity * Material.Ka;
  vec3 diffuse = phongModel(pos, normal, albedo);

  vec4 p = vec4(vec3(pos), 0.0);

  int count = 0;
  for(int i = 0; i < NumSamples; ++i)
  {
    vec2 coord = vec2(rand(gl_FragCoord.xy), rand(gl_FragCoord.yz));
    vec3 sampleData = texture(SampleMap, coord).xyz * 2.0-1.0;
    
    // Detemine sampling radius
    sampleData *= SampleRadius;

    // Based on normal, hemi-sphere sampling
    if(dot(normalize(sampleData-p.xyz), normal) < 0.0)
      sampleData *= -1.0;
    
    vec4 q = ProjectionMatrix * (p + vec4(vec3(sampleData), 1.0));

    // Convert to texture coord
    q = q * 0.5 / q.w + 0.5;

    // Compare the depth of textre and sample points
    if(q.z < texture(DepthMap, q.xy).z)
      ++count;
  }

  float a = clamp(2.0 * float(count) / float(NumSamples), 0.0, 1.0);

  //FragColor= vec4(diffuse + ambient * a, 1.0);
  //@comment only AO
  //FragColor= vec4(vec3(a), 1.0);
  FragColor = texture(SampleMap, TexCoord);
  //vec2 coord = vec2(rand(gl_FragCoord.xy), rand(gl_FragCoord.yz));
  //FragColor = texture(SampleMap, TexCoord);
}

void main()
{
  RenderPass();
}
