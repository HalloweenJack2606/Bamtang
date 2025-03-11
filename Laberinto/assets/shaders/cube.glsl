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
    gl_Position = u_ViewProjection * a_Position;
}

#shader fragment
#version 410 core

in vec4 v_Output_Color;
in vec2 v_Output_TexCoord;

layout(location = 0) out vec4 color;

void main()
{
    color = v_Output_Color;
}