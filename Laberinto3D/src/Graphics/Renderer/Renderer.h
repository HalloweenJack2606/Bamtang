#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader/Shader.h"
#include "Graphics/Resources/Texture/Texture.h"

struct QuadVertex
{
    vec3 Position;
    vec2 TextureCoords;
    int32 TextureID;
    vec4 QuadColor;
};

struct RendererData
{
    uint32 vao;
    uint32 vbo;

    std::array<vec4, 36> cubeVertexPositions;
    std::array<vec2, 36> cubeTextureCoords;

    QuadVertex* quadVertexBase = nullptr;
    QuadVertex* quadVertexPtr = nullptr;

    Shader shader;
    Texture texture;

    uint32 cubeCount;
};

class Renderer
{
public:
    static void Init();
    static void Shutdown();

    static void DrawCube(vec3 position, vec3 size, uint32 textureId, Color color);

    static void BeginScene(mat4 pvm);
    static void EndScene();
private:
    static void Flush();
private:
    inline static RendererData s_Data;
};