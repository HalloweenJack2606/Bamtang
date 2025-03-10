#shader vertex
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoords;
layout(location = 2) in vec4 a_Color;

uniform mat4 u_ViewProjection;

out vec4 v_Output_Color;
out vec2 v_Output_TexCoord;

void main()
{
	v_Output_TexCoord = a_TextureCoords;
	v_Output_Color = a_Color;
	gl_Position = u_ViewProjection * vec4(a_Position.xy, 0.0, 1.0);
}

#shader fragment
#version 410 core

in vec4 v_Output_Color;
in vec2 v_Output_TexCoord;

layout(location = 0) out vec4 color;

void main()
{
	vec2 uv = v_Output_TexCoord * 2.0 - 1.0;
	float thickness = 1.0;
	float fade = 0.05;

	float distance = 1.0 - length(uv);
	vec3 col = vec3(smoothstep(0.0, fade, distance));
	col *= vec3(smoothstep(thickness + fade, thickness, distance));

	if(col.rgb == vec3(0.0)) discard;

	color = vec4(col, 1.0) * v_Output_Color;
	//color = vec4(vec3(gl_FragCoord.z), 1.0);
}