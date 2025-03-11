#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader/Shader.h"

struct CircleVertex
{
    vec2 Position;
    vec2 TexCoords;
    Color CircleColor;
    float Thickness;
};

struct CircleRendererData
{
    uint32 circleCount = 0;

    uint32 vao = 0;
    uint32 vbo = 0;
    uint32 ibo = 0;
    vec4 quadVertexPositions[4];

    Shader shader;

    CircleVertex* circleVertexBase = nullptr;
    CircleVertex* circleVertexPtr = nullptr;
};

class CircleRenderer
{
public:
    static void Init();
    static void Shutdown();

    static void DrawCircle(vec2 position, float thickness, float size, Color color);

    static void BeginScene(mat4 pvm);
    static void EndScene();
private:
    static void Flush();
private:
    inline static CircleRendererData s_Data;
};
