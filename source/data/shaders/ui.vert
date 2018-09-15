/*
UI Vertex shader
*/

#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable


layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec4 in_color;

layout (location = 0) out vec4 out_color;
layout (location = 1) out vec2 out_uv;


layout(std140, binding = 1) uniform Viewport {
	mat4 proj_matrix;
} viewport ;



void main()
{
	gl_Position = viewport.proj_matrix * vec4(in_pos, 0.0, 1.0);

	out_color = in_color;
	out_uv = in_uv;
}
