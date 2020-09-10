#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 lightPos;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() 
{
	FragPos = vec3(Projection * View * Model * vec4(pos, 1.0f));
	gl_Position = Projection * View * Model * vec4(pos,1.f);
	Normal = mat3(transpose(inverse(View * Model))) * normal;
	TexCoord = texCoord;
}
