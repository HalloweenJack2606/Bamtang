#include "Graphics/Resources/Shader/Shader.h"
#include <glm/gtc/type_ptr.hpp>

void Shader::Init(const CString& path)
{
    m_FilePath = path;
    auto shaderSources = ReadShader(path);

    uint32 vertex = glCreateShader(GL_VERTEX_SHADER);
    uint32 fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vs = shaderSources[ShaderType::VERTEX].c_str();
    const char* fs = shaderSources[ShaderType::FRAGMENT].c_str();

    glShaderSource(vertex, 1, &vs, nullptr);
    glShaderSource(fragment, 1, &fs, nullptr);

    glCompileShader(vertex);
    glCompileShader(fragment);
    CheckErrors(vertex, "VERTEX");
    CheckErrors(fragment, "FRAGMENT");

    m_ID = glCreateProgram();

    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    auto lastSlash = m_FilePath.find_last_of("/\\");
    lastSlash = lastSlash == CString::npos ? 0 : lastSlash + 1;
    auto lastDot = m_FilePath.find('.');
    auto count = lastDot == CString::npos ? m_FilePath.size() - lastSlash : lastDot - lastSlash;
    m_Name = m_FilePath.substr(lastSlash, count);
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

std::unordered_map<ShaderType, CString> Shader::ReadShader(const CString& filepath)
{
    ShaderType type = ShaderType::NONE;

    std::unordered_map<ShaderType, CString> shaderSources;
    std::ifstream file(filepath);

    if (file)
    {
        CString line;
        std::stringstream ss[3];
        while (std::getline(file, line))
        {
            if (line.find("#shader") != CString::npos)
            {
                if (line.find("vertex") != CString::npos) type = ShaderType::VERTEX;
                else if (line.find("fragment") != CString::npos) type = ShaderType::FRAGMENT;
                else if (line.find("geometry") != CString::npos) type = ShaderType::GEOMETRY;
            }
            else
            {
                if(type == ShaderType::NONE)
                {
                    std::cout << "Error reading shader type" << std::endl;
                }
                else
                {
                    ss[(int)type] << line << '\n';
                }
            }
        }
        file.close();

        shaderSources[ShaderType::VERTEX] = ss[(int)ShaderType::VERTEX].str();
        shaderSources[ShaderType::FRAGMENT] = ss[(int)ShaderType::FRAGMENT].str();
        shaderSources[ShaderType::GEOMETRY] = ss[(int)ShaderType::GEOMETRY].str();
    }
    else
    {
        std::cout << "Could not open file: " << filepath << std::endl;
    }

    return shaderSources;
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetMat4(const CString& name, const mat4& value)
{
    const GLint location = glGetUniformLocation(m_ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::CheckErrors(const unsigned int& shader, const char* name)
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
