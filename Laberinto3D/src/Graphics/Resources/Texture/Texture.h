#pragma once
#include "Core/CoreMinimal.h"

class Texture
{
public:
    ~Texture();
    void Create(const CString& path);

    void Bind(uint32 slot = 0);
    void Unbind() const;
private:
    uint32 m_CurrentSlot = 0;
    uint32 m_ID;
};