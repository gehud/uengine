#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;

out vec2 v_UV;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_UV = a_UV;
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 o_Color;

in vec2 v_UV;

void main()
{
	o_Color = vec4(v_UV, 0.0, 1.0);
}