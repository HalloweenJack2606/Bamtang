#pragma once
#include "Core/CoreMinimal.h"
#include "Core/Window/Window.h"

struct CommandLineArgs
{
    int32 count = 0;
    char** args = nullptr;

    const char* operator[](uint32 index) const
    {
        return args[index];
    }
};

class Application
{
private:
    explicit Application(CommandLineArgs args);
    friend int main(int argc, char** argv);
    void Run();
private:
    Window* m_pWindow = nullptr;
};
