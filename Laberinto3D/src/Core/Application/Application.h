#pragma once
#include "Core/CoreMinimal.h"
#include "Core/Window/Window.h"

class Application
{
private:
    friend int main(int argc, char** argv);
    Application() = default;
    void Run();
private:
    Window m_Window;
};