#pragma once
#include "Core/CoreMinimal.h"
#include "World/Camera/Camera.h"
#include "Graphics/Resources/Shader/Shader.h"

struct CubeVertex {
    vec4 Position;
    vec2 TextureCoords;
    vec4 Color;
};

class CubeRenderer
{
public:
    static void Init();
    static void Shutdown();

    inline static void SetShader(const Shader& shader) noexcept { s_Shader = shader; }

    static void DrawCube(const vec3& position, const vec3& size, const Color& color);

    static void BeginScene(const Camera& camera);
    static void EndScene();
private:
    static void Flush();
private:
    inline static Shader s_Shader;
    inline static uint32 s_CubeVAO;
    inline static uint32 s_CubeVBO;
    inline static uint32 s_CubeIBO;

    inline static CubeVertex* s_CubeVertexBufferBase = nullptr;
    inline static CubeVertex* s_CubeVertexBufferPtr = nullptr;

    inline static vec4 s_CubeVertexPositions[8];

    inline static uint32 s_CubeCount = 0;
};
