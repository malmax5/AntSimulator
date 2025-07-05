#include "../../include/model/PheromoneMap.hpp"

#include <QDebug>

PheromoneMap::PheromoneMap(int width, int height)
    : width(width), height(height)
{
    map.resize(width);

    for (int x = 0; x < width; x++)
    {
        map[x].resize(height, 0);
    }
}

void PheromoneMap::addPheromone(const QPointF& pos, qreal strength)
{
    int x = toIndexX(pos.x());
    int y = toIndexY(pos.y());

    if (isValid(x, y))
    {
        map[x][y] += strength;
    }
}

void PheromoneMap::evaporate()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            map[x][y] *= evaporateRate;

            if (map[x][y] - 0.01 < 0)
            {
                map[x][y] = 0;
            }
        }
    }
}

QPointF PheromoneMap::getDirection(const QPointF& pos) const
{
    int x = toIndexX(pos.x());
    int y = toIndexY(pos.y());

    if (!isValid(x, y))
    {
        return QPointF(0, 0);
    }

    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static const int dy[] ={-1,-1,-1, 0, 0, 1, 1, 1};

    qreal maxStrength = -1;
    int bestDir = 0;

    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny))
        {
            if (map[nx][ny] > maxStrength)
            {
                maxStrength = map[nx][ny];
                bestDir = i;
            }
        }
    }

    if (maxStrength == 0)
    {
        return QPointF();
    }

    return QPointF(dx[bestDir], dy[bestDir]);
}

inline int PheromoneMap::toIndexX(qreal x) const
{
    return round(x);
}

inline int PheromoneMap::toIndexY(qreal y) const
{
    return round(y);
}

inline bool PheromoneMap::isValid(int x, int y) const
{
    return x >= 0 && y >= 0 && x < width && y < height;
}

int PheromoneMap::getWidth()
{
    return width;
}

int PheromoneMap::getHeight()
{
    return height;
}

qreal PheromoneMap::getValue(int x, int y) const
{
    return map[x][y];
}

void PheromoneMap::clear()
{
    for (int x = 0; x < width; x++)
    {
        map[x].clear();
    }
}
