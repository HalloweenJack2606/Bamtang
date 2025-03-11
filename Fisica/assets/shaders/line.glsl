#shader vertex
#version 410 core
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_ProjectionView;

void main()
{
    gl_Position = u_ProjectionView * vec4(a_Position, 0.0, 1.0);
    v_Color = a_Color;
}

#shader fragment
#version 410 core
in vec4 v_Color;
out vec4 color;

void main()
{
    color = v_Color;
}