#include "Graphics/LineRenderer/LineRenderer.h"
#define GLEW_STATIC
#include <GL/glew.h>

constexpr static uint32 g_MaxLines = 1;
constexpr static uint32 g_MaxVertices = g_MaxLines * 2 ;
constexpr static uint32 g_VBOAllocationSize = g_MaxVertices * sizeof(LineVertex);

void LineRenderer::Init(const mat4& pvm)
{
    s_Data.shader.Init("assets/shaders/line.glsl");
    s_Data.pvm = pvm;
    glGenVertexArrays(1, &s_Data.vao);
    glBindVertexArray(s_Data.vao);

    glGenBuffers(1, &s_Data.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
    glBufferData(GL_ARRAY_BUFFER, g_VBOAllocationSize, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, LineColor));

    glBindVertexArray(0);

    s_Data.lineVertexBase = new LineVertex[g_MaxVertices];
    s_Data.lineVertexPtr = s_Data.lineVertexPtr;
}

void LineRenderer::Shutdown()
{
    glDeleteVertexArrays(1, &s_Data.vao);
    glDeleteBuffers(1, &s_Data.vbo);
}

void LineRenderer::DrawLine(vec2 start, vec2 end, Color color)
{
    s_Data.lineVertexPtr = s_Data.lineVertexBase;
    s_Data.lineVertexPtr->Position = start;
    s_Data.lineVertexPtr->LineColor = color;
    s_Data.lineVertexPtr++;
    s_Data.lineVertexPtr->Position = end;
    s_Data.lineVertexPtr->LineColor = color;
    s_Data.lineVertexPtr++;
    auto dataSize = (uint32)((uint8*)s_Data.lineVertexPtr - (uint8*)s_Data.lineVertexBase);
    s_Data.shader.Bind();
    s_Data.shader.SetMatrix4("u_ProjectionView", s_Data.pvm);
    glBindVertexArray(s_Data.vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_Data.lineVertexBase);
    glDrawArrays(GL_LINES, 0, 2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
