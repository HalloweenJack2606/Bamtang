#include "Graphics/Resources/Shader/Shader.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void Shader::Init(const CString& path)
{
    m_FilePath = path;
    ShaderSources sources = ReadSources(path);

    m_ID = glCreateProgram();

    uint32 vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexSource = sources[ShaderType::VERTEX].c_str();
    const char* fragmentSource = sources[ShaderType::FRAGMENT].c_str();

    glShaderSource(vertex, 1, &vertexSource, 0);
    glShaderSource(fragment, 1, &fragmentSource, 0);

    glCompileShader(vertex);
    glCompileShader(fragment);

    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);

    glLinkProgram(m_ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

ShaderSources Shader::ReadSources(const CString& path)
{
    ShaderSources sources;
    std::ifstream file(path);
    if(file.is_open())
    {
        ShaderType currentType = ShaderType::NONE;
        CString line;
        std::stringstream ss[2];
        while(std::getline(file, line))
        {
            if(line.find("#shader") != CString::npos)
            {
                if(line.find("vertex") != CString::npos) currentType = ShaderType::VERTEX;
                if(line.find("fragment") != CString::npos) currentType = ShaderType::FRAGMENT;
            }
            else
            {
                if(currentType != ShaderType::NONE)
                {
                    ss[(uint32)currentType] << line << '\n';
                }
            }
        }

        sources[ShaderType::VERTEX] = ss[0].str();
        sources[ShaderType::FRAGMENT] = ss[1].str();
    }

    return sources;
}

void Shader::SetMat4(const CString& name, const mat4& value)
{
    auto location = glGetUniformLocation(m_ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
