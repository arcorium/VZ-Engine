#version 460 core

layout (location=0) in vec3 a_pos;
//layout(location=1) in vec3 a_color;

//uniform int u_t;

//out vec3 v_color;

void main()
{
	gl_Position = vec4(a_pos, 1.0f);
//	v_color = a_color;
}