#include "Graphics/CubeRenderer/CubeRenderer.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

constexpr static uint32 maxCubes = 20000;
constexpr static uint32 maxVertices = maxCubes * 8;
constexpr static uint32 indexCount = 6 * 2 * 3;
constexpr static uint32 maxIndices = maxCubes * indexCount;
constexpr static uint32 vboAllocationSize = sizeof(CubeVertex) * maxVertices;

void CubeRenderer::Init()
{
    s_CubeVertexBufferBase = new CubeVertex[maxVertices];
    glGenVertexArrays(1, &s_CubeVAO);
    glBindVertexArray(s_CubeVAO);

    glGenBuffers(1, &s_CubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, s_CubeVBO);
    glBufferData(GL_ARRAY_BUFFER, vboAllocationSize, nullptr, GL_DYNAMIC_DRAW);

    s_CubeVertexPositions[0] = { -0.5f, -0.5f, -0.5f, 1.0f };
    s_CubeVertexPositions[1] = {  0.5f, -0.5f, -0.5f, 1.0f };
    s_CubeVertexPositions[2] = {  0.5f,  0.5f, -0.5f, 1.0f };
    s_CubeVertexPositions[3] = { -0.5f,  0.5f, -0.5f, 1.0f };
    s_CubeVertexPositions[4] = { -0.5f, -0.5f,  0.5f, 1.0f };
    s_CubeVertexPositions[5] = {  0.5f, -0.5f,  0.5f, 1.0f };
    s_CubeVertexPositions[6] = {  0.5f,  0.5f,  0.5f, 1.0f };
    s_CubeVertexPositions[7] = { -0.5f,  0.5f,  0.5f, 1.0f };

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void*)offsetof(CubeVertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void*)offsetof(CubeVertex, TextureCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void*)offsetof(CubeVertex, Color));

    auto* cubeIndices = new uint32[maxIndices];
    uint32 offset = 0;
    for(uint32 i = 0; i < maxIndices; i += indexCount)
    {
        cubeIndices[i +  0] = offset + 4; cubeIndices[i +  1] = offset + 5; cubeIndices[i +  2] = offset + 6;
        cubeIndices[i +  3] = offset + 6; cubeIndices[i +  4] = offset + 7; cubeIndices[i +  5] = offset + 4;

        cubeIndices[i +  6] = offset + 1; cubeIndices[i +  7] = offset + 0; cubeIndices[i +  8] = offset + 3;
        cubeIndices[i +  9] = offset + 3; cubeIndices[i + 10] = offset + 2; cubeIndices[i + 11] = offset + 1;

        cubeIndices[i + 12] = offset + 0; cubeIndices[i + 13] = offset + 4; cubeIndices[i + 14] = offset + 7;
        cubeIndices[i + 15] = offset + 7; cubeIndices[i + 16] = offset + 3; cubeIndices[i + 17] = offset + 0;

        cubeIndices[i + 18] = offset + 5; cubeIndices[i + 19] = offset + 1; cubeIndices[i + 20] = offset + 2;
        cubeIndices[i + 21] = offset + 2; cubeIndices[i + 22] = offset + 6; cubeIndices[i + 23] = offset + 5;

        cubeIndices[i + 24] = offset + 0; cubeIndices[i + 25] = offset + 1; cubeIndices[i + 26] = offset + 5;
        cubeIndices[i + 27] = offset + 5; cubeIndices[i + 28] = offset + 4; cubeIndices[i + 29] = offset + 0;

        cubeIndices[i + 30] = offset + 3; cubeIndices[i + 31] = offset + 7; cubeIndices[i + 32] = offset + 6;
        cubeIndices[i + 33] = offset + 6; cubeIndices[i + 34] = offset + 2; cubeIndices[i + 35] = offset + 3;

        offset += 8;
    }

    glGenBuffers(1, &s_CubeIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_CubeIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(uint32), cubeIndices, GL_DYNAMIC_DRAW);
    delete[] cubeIndices;

    glBindVertexArray(0);
}

void CubeRenderer::Shutdown()
{
    glDeleteVertexArrays(1, &s_CubeVAO);
    glDeleteBuffers(1, &s_CubeIBO);
    glDeleteBuffers(1, &s_CubeVBO);
}

void CubeRenderer::DrawCube(const vec3& position, const vec3& size, const Color& color)
{
    mat4 transform = glm::translate(mat4(1.0f), position) * glm::scale(mat4(1.0f), size);
    static const vec2 texCoords[8] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

    for(int i = 0; i < 8; i++)
    {
        s_CubeVertexBufferPtr->Position = transform * s_CubeVertexPositions[i];
        s_CubeVertexBufferPtr->TextureCoords = texCoords[i];
        s_CubeVertexBufferPtr->Color = color;

        s_CubeVertexBufferPtr++;
    }

    s_CubeCount++;
}

void CubeRenderer::BeginScene(const Camera& camera)
{
    s_Shader.Bind();
    s_Shader.SetMat4("u_ViewProjection", camera.GetProjectionView());
    glBindVertexArray(s_CubeVAO);
    s_CubeVertexBufferPtr = s_CubeVertexBufferBase;
    s_CubeCount = 0;
}

void CubeRenderer::EndScene()
{
    Flush();
}

void CubeRenderer::Flush()
{
    auto dataSize = (uint32)((uint8*)s_CubeVertexBufferPtr - (uint8*)s_CubeVertexBufferBase);
    if(dataSize)
    {
        glBindVertexArray(s_CubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, s_CubeVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_CubeVertexBufferBase);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_CubeIBO);
        glDrawElements(GL_TRIANGLES, (int32)s_CubeCount * (int32)indexCount, GL_UNSIGNED_INT, nullptr);
    }
}
