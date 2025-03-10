#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Core/CoreMinimal.h"

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
    GEOMETRY = 2
};

class Shader
{
public:
    Shader() = default;
    void Init(const CString& path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    [[nodiscard, maybe_unused]] inline CString GetName() const { return m_Name; }
    [[nodiscard, maybe_unused]] inline CString GetPath() const { return m_FilePath; }

    void SetMat4(const CString& name, const mat4& value);
private:
    [[nodiscard]] std::unordered_map<ShaderType, CString> ReadShader(const CString& filepath);

    void CheckErrors(const unsigned int& shader, const char* name);
private:
    uint32 m_ID = 0;

    CString m_FilePath;
    CString m_Name;
};
