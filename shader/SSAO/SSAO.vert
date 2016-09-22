#version 400

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

subroutine (RenderPassType)
void renderGBuffer()
{
    Position = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0));
    Normal = normalize( NormalMatrix * VertexNormal );

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}

subroutine (RenderPassType)
void render()
{
	TexCoord = VertexPosition.xy;
	gl_Position = vec4(VertexPosition.xy * 2.0 - 1.0, 0.0, 1.0);
}

void main()
{
	RenderPass();
}