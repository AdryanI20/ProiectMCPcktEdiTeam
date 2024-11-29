#include "Map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

Map::Map(int rows,int cols): m_rows(rows), m_cols(cols){
    m_grid.resize(rows, std::vector<CellType>(cols, FREE_SPACE));
}

void Map::createRandomMap() {
    srand(time(NULL));
    std::vector<int> cellTypeChanse = {20, 50, 30};

    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            int randValue = rand() % 100;
            
            if (randValue < cellTypeChanse[0])
                m_grid[i][j] = static_cast<CellType>(0);
            else if (randValue < cellTypeChanse[0] + cellTypeChanse[1])
                m_grid[i][j] = static_cast<CellType>(1);
            else
                m_grid[i][j] = static_cast<CellType>(2);

            //m_grid[i][j] = static_cast<CellType>(randValue);
        }
    }

    createPath({ m_rows / 2, m_cols / 2 }, { 0, 0 });
    createPath({ m_rows / 2, m_cols / 2 }, { 0, m_cols - 1 });
    createPath({ m_rows / 2, m_cols / 2 }, { m_rows - 1, 0 });
    createPath({ m_rows / 2, m_cols / 2 }, { m_rows - 1, m_cols - 1 });
}

void Map::createPath(std::pair<int, int> start, std::pair<int, int> finish)
{
    std::pair<int, int> currentPosition = start;

    while (currentPosition != finish)
    {
        m_grid[currentPosition.first][currentPosition.second] = static_cast<CellType>(0);

        if (rand() % 2 == 0)
        {
            if (currentPosition.first != finish.first)
                currentPosition.first += static_cast<int>(currentPosition.first < finish.first) * 2 - 1;
            else
                currentPosition.second += static_cast<int>(currentPosition.second < finish.second) * 2 - 1;
        }
        else
        {
            if (currentPosition.second != finish.second)
                currentPosition.second += static_cast<int>(currentPosition.second < finish.second) * 2 - 1;
            else
                currentPosition.first += static_cast<int>(currentPosition.first < finish.first) * 2 - 1;
        }
    }

    m_grid[currentPosition.first][currentPosition.second] = static_cast<CellType>(0);
}

std::vector<CellType> Map::getNeighboursVal(int X, int Y)
{
    std::vector<CellType> neighbours;
    if (X + 1 < m_grid.size()) //RIGHT
        neighbours.push_back(m_grid[X + 1][Y]); //emplace_back(X + 1, Y);
    if (X - 1 >= 0) //LEFT
        neighbours.push_back(m_grid[X - 1][Y]); //.emplace_back(X - 1, Y);
    if (Y + 1 < m_grid[X].size()) //DOWN
        neighbours.push_back(m_grid[X][Y + 1]); //.emplace_back(X, Y + 1);
    if (Y - 1 >= 0) //UP
        neighbours.push_back(m_grid[X][Y - 1]); //.emplace_back(X, Y - 1);
    return neighbours;
}

std::string Map::getMapString() {
    std::string MapOutput;
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char TileType;
            switch (m_grid[i][j]) {
            case FREE_SPACE:
                TileType = ' ';
                break;
            case DESTRUCTIBIL_WALL:
                TileType = 'M';
                break;
            case INDESTRUCTIBIL_WALL:
                TileType = 'W';
                break;
            case BOMB_WALL:
                TileType = 'B';
                break;
            case PLAYER:
                TileType = '@';
                break;
            }
            MapOutput += TileType;
        }
        MapOutput += "\n";
    }
    //
    //for (int i = 0; i < m_rows; ++i) {
        //for (int j = 0; j < m_cols; ++j) {
            //std::cout << m_grid[i][j] << " ";
        //}
        //std::cout << "\n";
    //}
    //
    return MapOutput;
}

void Map::setPositionValue(int X, int Y, CellType value)
{
    if (X >= 0 && X < m_grid.size())
        if (Y >= 0 && Y < m_grid[X].size())
            m_grid[X][Y] = value;
}

CellType Map::getPositionValue(int X, int Y)
{
    if (X >= 0 && X < m_grid.size())
        if (Y >= 0 && Y < m_grid[X].size())
            return m_grid[X][Y];
    return CellType::VOID;
}

std::pair<int, int> Map::getSize()
{
    return { m_rows, m_cols };
}