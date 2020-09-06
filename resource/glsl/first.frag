#version 460 core

out vec4 color;

in vec3 pass_color;

uniform float time;

void main()
{
	color = vec4(pass_color,1) * vec4(0.5 + 0.5*sin(time*4+vec3(0,2,4)),1);
}