#pragma once
#include <iostream>

typedef uint32_t uint32;
typedef int32_t int32;

struct iVec2
{
    int32 x;
    int32 y;
};

inline iVec2 operator+(const iVec2& lhs, const iVec2& rhs)
{
    return iVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

class Maze
{
public:
    void Generate(uint32 size);
    void Print() const;

    [[nodiscard, maybe_unused]] inline uint32 GetSize() const { return m_Size; }
private:
    void DFS(iVec2 position);
    [[nodiscard]] iVec2 FindFarthestFromA();
    [[nodiscard]] bool IsValid(iVec2 position) const;

    [[nodiscard]] char At(iVec2 position) const;
    void SetAt(iVec2 position, char value);
public:
    typedef std::vector<std::vector<char>> MazeData;
    MazeData data;
private:
    typedef std::vector<iVec2> Directions;
    Directions m_Directions = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    uint32 m_Size = 0;
};
