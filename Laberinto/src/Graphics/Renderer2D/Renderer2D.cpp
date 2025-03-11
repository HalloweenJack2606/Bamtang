#include "Graphics/Renderer2D/Renderer2D.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

constexpr static uint32 maxQuads = 20000;
constexpr static uint32 maxVertices = maxQuads * 4;
constexpr static uint32 indexCount = 6;
constexpr static uint32 maxIndices = maxQuads * indexCount;
constexpr static uint32 vboAllocationSize = sizeof(QuadVertex) * maxVertices;

void Renderer2D::Init()
{
    s_QuadVertexBufferBase = new QuadVertex[maxVertices];

    glGenVertexArrays(1, &s_QuadVAO);
    glBindVertexArray(s_QuadVAO);

    glGenBuffers(1, &s_QuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, s_QuadVBO);
    glBufferData(GL_ARRAY_BUFFER, vboAllocationSize, nullptr, GL_DYNAMIC_DRAW);

    s_QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    s_QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
    s_QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
    s_QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, TextureCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Color));

    auto* quadIndices = new uint32[maxIndices];

    uint32 offset = 0;
    for(uint32 i = 0; i < maxIndices; i+=6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;
        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    glGenBuffers(1, &s_QuadIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(uint32), quadIndices, GL_DYNAMIC_DRAW);


    delete[] quadIndices;

    glBindVertexArray(0);
}

void Renderer2D::Shutdown()
{
    glDeleteVertexArrays(1, &s_QuadVAO);
    glDeleteBuffers(1, &s_QuadIBO);
    glDeleteBuffers(1, &s_QuadVBO);
}

void Renderer2D::BeginScene(const Camera& camera)
{
    s_Shader.Bind();
    s_Shader.SetMat4("u_ViewProjection", camera.GetProjectionView());
    glBindVertexArray(s_QuadVAO);
    s_QuadVertexBufferPtr = s_QuadVertexBufferBase;
}

void Renderer2D::DrawQuad(const vec2 position, vec2 size, const vec4 color)
{
    static constexpr vec2 texCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

    static constexpr uint32 quadVertexCount = 4;

    mat4 transform = glm::translate(mat4(1.0f), vec3(position, 0.0f)) * glm::scale(mat4(1.0f), vec3(size, 1.0f));

    for(uint32 i = 0; i < quadVertexCount; i++)
    {
        s_QuadVertexBufferPtr->Position = transform * s_QuadVertexPositions[i];
        s_QuadVertexBufferPtr->TextureCoords = texCoords[i];
        s_QuadVertexBufferPtr->Color = color;
        s_QuadVertexBufferPtr++;
    }

    s_QuadCount++;
}

void Renderer2D::Flush()
{
    auto dataSize = (uint32)((uint8*)s_QuadVertexBufferPtr - (uint8*)s_QuadVertexBufferBase);
    if(dataSize)
    {
        glBindBuffer(GL_ARRAY_BUFFER, s_QuadVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_QuadVertexBufferBase);

        s_Shader.Bind();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadIBO);
        glDrawElements(GL_TRIANGLES, s_QuadCount * indexCount, GL_UNSIGNED_INT, nullptr);
        s_Shader.Unbind();
    }
}

void Renderer2D::EndScene()
{
    Flush();
}
