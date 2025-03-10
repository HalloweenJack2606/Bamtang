#pragma once
#include <iostream>

typedef uint32_t uint32;
typedef int32_t int32;

struct vec2
{
    float x;
    float y;
};

inline vec2 operator+(const vec2& lhs, const vec2& rhs)
{
    return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

class Maze
{
public:
    void Generate(uint32 size);
    void Print() const;

    [[nodiscard]] char At(vec2 position) const;

    [[nodiscard, maybe_unused]] inline uint32 GetSize() const { return m_Size; }
private:
    void DFS(vec2 position);
    [[nodiscard]] vec2 FindFarthestFromA() const;
    [[nodiscard]] bool IsValid(vec2 position) const;

    void SetAt(vec2 position, char value);
public:
    typedef std::vector<std::vector<char>> MazeData;
    MazeData data;
private:
    typedef std::vector<vec2> Directions;
    Directions m_Directions = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    uint32 m_Size = 0;
};