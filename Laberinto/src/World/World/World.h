#pragma once
#include "World/Maze/Maze.h"
#include "Core/CoreMinimal.h"

class World
{
public:
    void Init();

    void OnUpdate();
private:
    Maze m_Maze;
};
