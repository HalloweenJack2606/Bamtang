#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader/Shader.h"
#include "World/Camera/Camera.h"

struct QuadVertex
{
    vec4 Position;
    vec2 TextureCoords;
    vec4 Color;
};

class Renderer2D
{
public:
    static void Init();
    static void Shutdown();

    static void SetShader(Shader& shader) { s_Shader = shader; }

    static void BeginScene(const Camera& camera);
    static void EndScene();

    static void DrawQuad(vec2 position, vec2 size, vec4 color);
private:
    static void Flush();
private:
    inline static Shader s_Shader;

    inline static uint32 s_QuadVAO;
    inline static uint32 s_QuadVBO;
    inline static uint32 s_QuadIBO;

    inline static vec4 s_QuadVertexPositions[4];

    inline static QuadVertex* s_QuadVertexBufferBase = nullptr;
    inline static QuadVertex* s_QuadVertexBufferPtr = nullptr;

    inline static uint32 s_QuadCount = 0;
};
