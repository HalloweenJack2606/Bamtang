#shader vertex
#version 410 core

layout(location=0) in vec2 a_Position;
layout(location=1) in vec2 a_TexCoords;
layout(location=2) in vec4 a_Color;
layout(location=3) in float a_Thickness;

uniform mat4 u_ProjectionView;

out vec2 v_TexCoords;
out vec4 v_Color;
out float v_Thickness;

void main()
{
    v_Color = a_Color;
    v_Thickness = a_Thickness;
    v_TexCoords = a_TexCoords;
    gl_Position = u_ProjectionView * vec4(a_Position, 0.0, 1.0);
}

#shader fragment
#version 410 core

in vec2 v_TexCoords;
in vec4 v_Color;
in float v_Thickness;

layout(location=0) out vec4 color;

void main()
{
    vec2 uv = v_TexCoords * 2.0 - 1.0;
    float thickness = v_Thickness;
    float fade = 0.05;

    float distance = 1.0 - length(uv);
    vec3 col = vec3(smoothstep(0.0, fade, distance));
    col *= vec3(smoothstep(thickness + fade, thickness, distance));

    float alpha = 1.0;
    if(col.rgb == vec3(0.0)) alpha = 0.0;
    color = vec4(col, alpha) * v_Color;
    //color = v_Color;
}
