#version 460 core

layout (location = 0) in vec3 position;

in vec3 color;

uniform float time;

out vec3 pass_color;

void main()
{
	vec3 finalpos = (position-sin(time)*0.5);
	gl_Position = vec4(finalpos/15,1);
	pass_color = color;
}