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

void Maze::Generate(uint32 size)
{
    m_Size = size;
    data.assign(m_Size, std::vector<char>(m_Size, '*'));
    auto start = vec2(1, 1);
    DFS(start);
    vec2 end = FindFarthestFromA();
    SetAt(start, 'A');
    SetAt(end, 'B');
}

vec2 Maze::FindFarthestFromA() const
{
    vec2 start = {1, 1};

    std::vector<std::vector<uint32>> distances(m_Size, std::vector<uint32>(m_Size, -1));
    distances[(uint32)start.x][(uint32)start.y] = 0;

    std::queue<vec2> queue;
    queue.push(start);

    vec2 furthestPoint = start;
    uint32 maxDistance = 0;

    while (!queue.empty())
    {
        vec2 current = queue.front();
        queue.pop();
        static constexpr const vec2 directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        for (int i = 0; i < 4; i++)
        {
            vec2 next = {current.x + directions[i].x, current.y + directions[i].y};

            if (next.x >= 0 && next.x < m_Size && next.y >= 0 && next.y < m_Size &&
                data[(uint32)next.x][(uint32)next.y] == ' ' && distances[(uint32)next.x][(uint32)next.y] == -1)
            {
                distances[(uint32)next.x][(uint32)next.y] = distances[(uint32)current.x][(uint32)current.y] + 1;
                queue.push(next);

                if (distances[(uint32)next.x][(uint32)next.y] > maxDistance)
                {
                    maxDistance = distances[(uint32)next.x][(uint32)next.y];
                    furthestPoint = next;
                }
            }
        }
    }

    return furthestPoint;
}

bool Maze::IsValid(vec2 position) const
{
    return position.x > 0 && position.x < m_Size - 1 && position.y > 0 && position.y < m_Size - 1 && this->At(position) == '*';
}

void Maze::SetAt(vec2 position, const char value)
{
    data[(uint32)position.x][(uint32)position.y] = value;
}

char Maze::At(vec2 position) const
{
    return data[(uint32)position.x][(uint32)position.y];
}
