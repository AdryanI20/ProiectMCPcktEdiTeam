#include "Map.h"
#include "CellType.h"
#include <iostream>

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

//std::vector<std::vector<CellType>> Map::getMap() {
//    return m_grid;
//}

std::string Map::getMapString() {
    std::string MapOutput;
    for (int j = 0; j < m_cols + 2; j++) {
        MapOutput += ' ';
    }
    MapOutput += '\n';
    for (int i = 0; i < m_rows; ++i) {
        MapOutput += ' ';
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
            MapOutput += ' ';
//        MapOutput += "\n";
            for (int j = 0; j < m_cols + 2; ++j)
                MapOutput += ' ';
        }
        MapOutput += "\n";
    }
    return MapOutput;
}

void Map::placePlayer(int playerId, int row, int col) {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        std::cerr << "Pozitia (" << row << ", " << col << ") este in afara limitei hartii!\n";
        return;
    }
}
//