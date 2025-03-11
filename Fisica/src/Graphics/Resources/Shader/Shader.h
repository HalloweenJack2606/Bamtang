#pragma once
#include "Core/CoreMinimal.h"

enum class ShaderType
{
    VERTEX = 0,
    FRAGMENT = 1,
    NONE = -1
};

typedef std::unordered_map<ShaderType, CString> ShaderSourceMap;

class Shader
{
public:
    ~Shader();
    void Init(const CString& path);

    void Bind() const;
    void Unbind() const;

    void SetMatrix4(const CString& name, mat4 value);
private:
    [[nodiscard]] ShaderSourceMap ReadShader(const CString& path);
private:
    uint32 m_ID;
    CString m_Path;
};
