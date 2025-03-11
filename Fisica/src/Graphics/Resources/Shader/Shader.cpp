#include "Graphics/Resources/Shader/Shader.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void CheckErrors(const unsigned int& shader, const char* name)
{
    int status = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        int loglen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
        std::vector<char> log;
        log.reserve(loglen);
        GLsizei written = 0;
        glGetShaderInfoLog(shader, loglen, &written, log.data());
        std::cout << "Failed to compile " << name << " shader: " << log.data() << std::endl;
    }
}


Shader::~Shader()
{
    glDeleteProgram(m_ID);
}


void Shader::Init(const CString& path)
{
    m_Path = path;
    auto shaders = ReadShader(path);

    m_ID = glCreateProgram();

    uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    uint32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    auto vs = shaders[ShaderType::VERTEX].c_str();
    auto fs = shaders[ShaderType::FRAGMENT].c_str();

    glShaderSource(vertexShader, 1, &vs, nullptr);
    glShaderSource(fragmentShader, 1, &fs, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    CheckErrors(vertexShader, "VERTEX");
    CheckErrors(fragmentShader, "FRAGMENT");

    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

ShaderSourceMap Shader::ReadShader(const CString& path)
{
    ShaderSourceMap sources;
    ShaderType shaderType = ShaderType::NONE;

    std::ifstream file(path);

    if(file.is_open())
    {
        std::stringstream ss[3];
        CString line;
        while(std::getline(file, line))
        {
            if(line.find("#shader") != CString::npos)
            {
                if(line.find("vertex") != CString::npos) shaderType = ShaderType::VERTEX;
                else if(line.find("fragment") != CString::npos) shaderType = ShaderType::FRAGMENT;
            }
            else
            {
                if(shaderType != ShaderType::NONE) ss[(int32)shaderType] << line << '\n';
            }
        }

        file.close();

        sources[ShaderType::VERTEX] = ss[(int32)ShaderType::VERTEX].str();
        sources[ShaderType::FRAGMENT] = ss[(int32)ShaderType::FRAGMENT].str();
    }

    return sources;
}

void Shader::SetMatrix4(const CString& name, mat4 value)
{
    int32 location = glGetUniformLocation(m_ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
