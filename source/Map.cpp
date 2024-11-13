#include "Map.h"
#include "CellType.h"
#include "Direction.h"
#include "Character.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

Map::Map(int rows,int cols): m_rows(rows), m_cols(cols){
    m_grid.resize(rows, std::vector<CellType>(cols, FREE_SPACE));
}

void Map::createRandomMap() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            int randValue = rand() % 3;
            m_grid[i][j] = static_cast<CellType>(randValue);
        }
    }
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
                        type = 'W';
                        break;
                    case INDESTRUCTIBIL_WALL:
                        type = 'I';
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

//    for (size_t i = 0; i < characters.size(); ++i) {
//        int row = corners[i].first;
//        int col = corners[i].second;
//
//        characters[i].setPosition({static_cast<float>(row), static_cast<float>(col)});
//        m_grid[row][col] = PLAYER;
//
//    }
}
