#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader/Shader.h"

struct LineVertex
{
    vec2 Position;
    Color LineColor;
};

struct LineRendererData
{
    uint32 vao;
    uint32 vbo;

    LineVertex* lineVertexBase = nullptr;
    LineVertex* lineVertexPtr = nullptr;

    Shader shader;
    mat4 pvm;
};

class LineRenderer
{
public:
    static void Init(const mat4& pvm);
    static void Shutdown();

    static void DrawLine(vec2 start, vec2 end, Color color);
private:
    inline static LineRendererData s_Data;
};
