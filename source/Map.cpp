#include "Map.h"
#include "CellType.h"
#include "Direction.h"
#include "Character.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
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

    createPath(std::make_pair(m_rows / 2, m_cols / 2), std::make_pair(0, 0));
    createPath(std::make_pair(m_rows / 2, m_cols / 2), std::make_pair(0, m_cols - 1));
    createPath(std::make_pair(m_rows / 2, m_cols / 2), std::make_pair(m_rows - 1, 0));
    createPath(std::make_pair(m_rows / 2, m_cols / 2), std::make_pair(m_rows - 1, m_cols - 1));
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

std::string Map::getMapString() {
    std::string MapOutput;
    //    for (int j = 0; j < m_cols + 2; j++) {
    //        MapOutput += ' ';
    //    }
    //    MapOutput += '\n';
    //        MapOutput += ' ';/
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char type;
            switch (m_grid[i][j]) {
            case FREE_SPACE:
                type = ' ';
                break;
            case DESTRUCTIBIL_WALL:
                type = 'c';
                break;
            case INDESTRUCTIBIL_WALL:
                type = 'w';
                break;
            case PLAYER:
                type = '@';
                break;
            }
            MapOutput += type;
        }
        //            MapOutput += ' ';
        MapOutput += "\n";
        //            for (int j = 0; j < m_cols + 2; ++j)
        //                MapOutput += ' ';
    }
    //        MapOutput += "\n";
    return MapOutput;
}

void Map::placePlayer(int playerId, int row, int col) {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        std::cerr << "Pozitia (" << row << ", " << col << ") este in afara limitei hartii!\n";
        return;
    }
    if (m_grid[row][col] == FREE_SPACE) {
        m_grid[row][col] = PLAYER;
        std::cout << "Playerul " << playerId << " a fost plasat la (" << row << ", " << col << ")\n";
    } else {
        std::cerr << "Nu se poate plasa playerul " << playerId << " la (" << row << ", " << col << ") deoarece celula este ocupată!\n";
    }
}
bool Map::canMove(int row, int col, Direction direction)  {
    int newRow = row;
    int newCol = col;

    switch (direction) {
        case Direction::UP:
            newRow -= 1;
            break;
        case Direction::DOWN:
            newRow += 1;
            break;
        case Direction::LEFT:
            newCol -= 1;
            break;
        case Direction::RIGHT:
            newCol += 1;
            break;
    }
    if (newRow < 0 || newRow >= m_rows || newCol < 0 || newCol >= m_cols) {
        return false;
    }
    if (m_grid[newRow][newCol] == FREE_SPACE) {
        return true;
    }
    return false;
}
void Map::placeCharactersInCorners(std::vector<Character>& characters) {
    if (characters.size() < 2 || characters.size() > 4) {
        std::cerr << "Număr invalid de jucători. Trebuie să fie între 2 și 4.\n";
        return;
    }

    std::vector<std::pair<int, int>> corners = {
            {0, 0},                          // Stânga sus
            {0, m_cols - 1},                 // Dreapta sus
            {m_rows - 1, 0},                 // Stânga jos
            {m_rows - 1, m_cols - 1}         // Dreapta jos
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(corners.begin(), corners.end(), g);

    for (size_t i = 0; i < characters.size(); ++i) {
        int row = corners[i].first;
        int col = corners[i].second;

        characters[i].setPosition({static_cast<float>(row), static_cast<float>(col)});
        m_grid[row][col] = PLAYER;

    }
}
void Map::clearSurroundingsAroundPlayers() {
    std::vector<std::pair<int, int>> directions = {
            {-1, 0}, // Sus
            {1, 0},  // Jos
            {0, -1}, // Stânga
            {0, 1}   // Dreapta
    };

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (m_grid[i][j] == PLAYER) {
                for (const auto& dir : directions) {
                    int newRow = i + dir.first;
                    int newCol = j + dir.second;

                    if (newRow >= 0 && newRow < m_rows && newCol >= 0 && newCol < m_cols) {
                        if (m_grid[newRow][newCol] == INDESTRUCTIBIL_WALL) {
                            m_grid[newRow][newCol] = FREE_SPACE;
                        }
                    }
                }
            }
        }
    }
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