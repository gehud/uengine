#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection = mat4(1.0);
uniform mat4 u_Transform = mat4(1.0);

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

uniform vec4 u_Color = vec4(1);

void main()
{
	gl_FragColor = u_Color;
}