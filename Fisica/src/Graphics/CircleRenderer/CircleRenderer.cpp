#include "Graphics/CircleRenderer/CircleRenderer.h"
#include "glm/ext/matrix_transform.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

constexpr static uint32 g_MaxCircles = 100;
constexpr static uint32 g_MaxVertices = g_MaxCircles * 4;
constexpr static uint32 g_MaxIndices = g_MaxCircles * 6;
constexpr static uint32 g_VBOAllocationSize = g_MaxVertices * sizeof(CircleVertex);

void CircleRenderer::Init()
{
    s_Data.shader.Init("assets/shaders/circle.glsl");
    s_Data.circleVertexBase = new CircleVertex[g_MaxVertices];
    glGenVertexArrays(1, &s_Data.vao);
    glBindVertexArray(s_Data.vao);

    glGenBuffers(1, &s_Data.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
    glBufferData(GL_ARRAY_BUFFER, g_VBOAllocationSize, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (const void*)offsetof(CircleVertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (const void*)offsetof(CircleVertex, TexCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (const void*)offsetof(CircleVertex, CircleColor));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (const void*)offsetof(CircleVertex, Thickness));

    s_Data.quadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f};
    s_Data.quadVertexPositions[3] = {-0.5f,  0.5f, 0.0f, 1.0f};

    auto* quadIndices = new uint32[g_MaxIndices];

    uint32 offset = 0;
    for(int i = 0; i < g_MaxIndices; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    glGenBuffers(1, &s_Data.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_MaxIndices * sizeof(uint32), quadIndices, GL_DYNAMIC_DRAW);

    delete[]  quadIndices;

    glBindVertexArray(0);
}

void CircleRenderer::Shutdown()
{
    glDeleteVertexArrays(1, &s_Data.vao);
    glDeleteBuffers(1, &s_Data.vbo);
    glDeleteBuffers(1, &s_Data.ibo);
}

void CircleRenderer::DrawCircle(vec2 position, float thickness, float size, Color color)
{
    constexpr static vec2 texCoords[4] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    constexpr static uint32 vertexCount = 4;

    auto transform =  glm::translate(mat4(1.0f), vec3(position, 0.0f)) * glm::scale(mat4(1.0f), vec3(size));

    for(int i = 0; i < vertexCount; i++)
    {
        vec4 transformedPos = transform * s_Data.quadVertexPositions[i];
        s_Data.circleVertexPtr->Position = vec2(transformedPos.x, transformedPos.y);
        s_Data.circleVertexPtr->CircleColor = color;
        s_Data.circleVertexPtr->Thickness = thickness;
        s_Data.circleVertexPtr->TexCoords = texCoords[i];
        s_Data.circleVertexPtr++;
    }

    s_Data.circleCount++;
}

void CircleRenderer::BeginScene(mat4 pvm)
{
    s_Data.shader.Bind();
    s_Data.shader.SetMatrix4("u_ProjectionView", pvm);
    s_Data.circleVertexPtr = s_Data.circleVertexBase;
    glBindVertexArray(s_Data.vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.ibo);
    s_Data.circleCount = 0;
}

void CircleRenderer::EndScene()
{
    Flush();
    s_Data.shader.Unbind();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CircleRenderer::Flush()
{
    auto dataSize = uint32((uint8*)s_Data.circleVertexPtr - (uint8*)s_Data.circleVertexBase);

    if(dataSize)
    {
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_Data.circleVertexBase);
        glDrawElements(GL_TRIANGLES, s_Data.circleCount * 6 , GL_UNSIGNED_INT, nullptr);
    }
}
