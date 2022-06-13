#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection = mat4(1.0);
uniform mat4 u_Transform = mat4(1.0);

out vec3 v_Position;
out vec3 v_Normal;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Position = (u_Transform * vec4(a_Position, 1.0)).xyz;
	v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 o_Color;

uniform vec3 u_LightPosition;
uniform vec3 u_LightColor = vec3(1.0);
uniform float u_AmbientStrength = 0.2;
uniform vec3 u_ViewPosition;
uniform float u_SpecularStrength = 0.25;

uniform vec4 u_Color = vec4(1.0);

in vec3 v_Position;
in vec3 v_Normal;

void main()
{
	vec3 ambient = u_LightColor * u_AmbientStrength;

	vec3 norm = normalize(v_Normal);

	vec3 lightDir = normalize(u_LightPosition - v_Position);
	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = diff * u_LightColor;

	vec3 viewDir = normalize(u_ViewPosition - v_Position);
	vec3 reflectDir = reflect(-lightDir, v_Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = u_SpecularStrength * spec * u_LightColor; 

	o_Color = vec4((diffuse + ambient + specular), 1.0) * u_Color;
}