#include "Maze.h"
#include <random>

std::random_device g_RD;
std::mt19937 g_RNG(g_RD());

void Maze::Print() const
{
    for (const auto& row : data)
    {
        for (char cell : row)
        {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

void Maze::Generate(uint32 size)
{
    m_Size = size;
    data.assign(m_Size, std::vector<char>(m_Size, '*'));
    auto start = vec2(1, 1);
    DFS(start);
    vec2 end = FindFarthestFromA();
    SetAt(end, 'B');
    SetAt(start, 'A');
}

void Maze::DFS(vec2 position)
{
    const auto x = position.x;
    const auto y = position.y;
    SetAt(position, ' ');
    std::shuffle(std::begin(m_Directions), std::end(m_Directions), g_RNG);
    for (const auto& dir : m_Directions)
    {
        vec2 newPosition = position + dir;
        if (IsValid(newPosition))
        {
            SetAt(vec2(x + dir.x / 2, y + dir.y / 2), ' ');
            DFS(newPosition);
        }
    }
}

vec2 Maze::FindFarthestFromA()
{
    std::vector<std::vector<uint32>> matrix(m_Size, std::vector<uint32>(m_Size, -1));
    matrix[1][1] = 0;
    std::vector<vec2> queue = {{1, 1}};
    vec2 farthest = {1, 1};

    for (size_t i = 0; i < queue.size(); i++)
    {
        vec2 current = queue[i];
        for (const auto& direction : m_Directions)
        {
            int32 nextX = current.x + direction.x;
            int32 nextY = current.y + direction.y;
            if (nextX > 0 && nextY > 0 && nextX < m_Size && nextY < m_Size && data[nextX][nextY] == ' ' && matrix[nextX][nextY] == -1)
            {
                matrix[nextX][nextY] = matrix[current.x][current.y] + 1;
                queue.push_back({nextX, nextY});
                if (matrix[nextX][nextY] > matrix[farthest.x][farthest.y])
                {
                    farthest = {nextX, nextY};
                }
            }
        }
    }
    return farthest;
}

bool Maze::IsValid(vec2 position) const
{
    return position.x > 0 && position.x < m_Size - 1 && position.y > 0 && position.y < m_Size - 1 && this->At(position) == '*';
}

void Maze::SetAt(vec2 position, const char value)
{
    data[position.x][position.y] = value;
}

char Maze::At(vec2 position) const
{
    return data[position.x][position.y];
}
