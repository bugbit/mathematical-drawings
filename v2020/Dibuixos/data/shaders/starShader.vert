#version 330 core

layout(location=0) in vec4 in_position;

// Model, View, Projection matrix.
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(in_position.xyz, 1);
	//gl_Color = vec3(in_position.z,in_position.z,in_position.z);
}