#pragma once
#include "Core/CoreMinimal.h"

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

typedef std::unordered_map<ShaderType, CString> ShaderSources;

class Shader
{
public:
    ~Shader();
    void Init(const CString& path);

    void Bind() const;
    void Unbind() const;

    void SetMat4(const CString& name, const mat4& value);
private:
    ShaderSources ReadSources(const CString& path);
private:
    CString m_FilePath;
    uint32 m_ID;
};