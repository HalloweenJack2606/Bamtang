#include "Graphics/Renderer/Renderer.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

const uint32 g_MaxCubes = 10000;
const uint32 g_VerticesPerCube = 36;
const uint32 g_MaxVertices = g_MaxCubes * g_VerticesPerCube;
const uint32 g_VBOAllocationSize = sizeof(QuadVertex) * g_MaxVertices;

void Renderer::Init()
{
    s_Data.texture.Create("assets/textures/amogus.png");
    s_Data.shader.Init("assets/shaders/cube.glsl");
    s_Data.quadVertexBase = new QuadVertex[g_MaxVertices];
    s_Data.quadVertexPtr = s_Data.quadVertexBase;

    glGenVertexArrays(1, &s_Data.vao);
    glBindVertexArray(s_Data.vao);

    glGenBuffers(1, &s_Data.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
    glBufferData(GL_ARRAY_BUFFER, g_VBOAllocationSize, nullptr, GL_DYNAMIC_DRAW);

    s_Data.cubeVertexPositions = {{
            {-0.5f, -0.5f, -0.5f, 1.0f}, {0.5f, -0.5f, -0.5f, 1.0f}, {0.5f, 0.5f, -0.5f, 1.0f},
            {0.5f, 0.5f, -0.5f, 1.0f}, {-0.5f, 0.5f, -0.5f, 1.0f}, {-0.5f, -0.5f, -0.5f, 1.0f},

            {-0.5f, -0.5f, 0.5f, 1.0f}, {0.5f, -0.5f, 0.5f, 1.0f}, {0.5f, 0.5f, 0.5f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f}, {-0.5f, 0.5f, 0.5f, 1.0f}, {-0.5f, -0.5f, 0.5f, 1.0f},

            {-0.5f, 0.5f, 0.5f, 1.0f}, {-0.5f, 0.5f, -0.5f, 1.0f}, {-0.5f, -0.5f, -0.5f, 1.0f},
            {-0.5f, -0.5f, -0.5f, 1.0f}, {-0.5f, -0.5f, 0.5f, 1.0f}, {-0.5f, 0.5f, 0.5f, 1.0f},

            {0.5f, 0.5f, 0.5f, 1.0f}, {0.5f, 0.5f, -0.5f, 1.0f}, {0.5f, -0.5f, -0.5f, 1.0f},
            {0.5f, -0.5f, -0.5f, 1.0f}, {0.5f, -0.5f, 0.5f, 1.0f}, {0.5f, 0.5f, 0.5f, 1.0f},

            {-0.5f, -0.5f, -0.5f, 1.0f}, {0.5f, -0.5f, -0.5f, 1.0f}, {0.5f, -0.5f, 0.5f, 1.0f},
            {0.5f, -0.5f, 0.5f, 1.0f}, {-0.5f, -0.5f, 0.5f, 1.0f}, {-0.5f, -0.5f, -0.5f, 1.0f},

            {-0.5f, 0.5f, -0.5f, 1.0f}, {0.5f, 0.5f, -0.5f, 1.0f}, {0.5f, 0.5f, 0.5f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f}, {-0.5f, 0.5f, 0.5f, 1.0f}, {-0.5f, 0.5f, -0.5f, 1.0f}
    }};


    s_Data.cubeTextureCoords = {{
            {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

            {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

            {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
            {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},

            {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
            {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},

            {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

            {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}
    }};


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, TextureCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, TextureID));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, QuadColor));

    glBindVertexArray(0);
}

void Renderer::Shutdown()
{
    glDeleteVertexArrays(1, &s_Data.vao);
    glDeleteBuffers(1, &s_Data.vbo);
}

void Renderer::BeginScene(mat4 pvm)
{
    s_Data.shader.Bind();
    s_Data.shader.SetMat4("u_ViewProjection", pvm);
    glBindVertexArray(s_Data.vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
    s_Data.quadVertexPtr = s_Data.quadVertexBase;
    s_Data.cubeCount = 0;
}

void Renderer::EndScene()
{
    Flush();
}

void Renderer::Flush()
{
    auto dataSize = (uint32)((uint8*)s_Data.quadVertexPtr - (uint8*)s_Data.quadVertexBase);
    if(dataSize)
    {
        s_Data.texture.Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_Data.quadVertexBase);
        glDrawArrays(GL_TRIANGLES, 0, (int32)s_Data.cubeCount * (int32)g_VerticesPerCube);
    }
}

void Renderer::DrawCube(vec3 position, vec3 size, uint32 textureId, Color color)
{
    mat4 transform = glm::translate(mat4(1.0f), position) * glm::scale(mat4(1.0f), size);

    for(int i = 0; i < g_VerticesPerCube; i++)
    {
        s_Data.quadVertexPtr->Position = transform * s_Data.cubeVertexPositions[i];
        s_Data.quadVertexPtr->TextureCoords = s_Data.cubeTextureCoords[i];
        s_Data.quadVertexPtr->TextureID = (int32)textureId;
        s_Data.quadVertexPtr->QuadColor = color;
        s_Data.quadVertexPtr++;
    }

    s_Data.cubeCount++;
}
