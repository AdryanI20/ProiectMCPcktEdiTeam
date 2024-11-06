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
    for(int i =0;i<m_rows;++i) {
        for(int j =0;j<m_cols;++j) {
            char type;
            switch(m_grid[i][j]){
            case 0:
                type = ' ';
                break;
            case 1:
                type = 'W';
                break;
            case 2:
                type = 'I';
                break;
            }
            MapOutput += type;
        }
//        MapOutput += "\n";
    }
    return MapOutput;
}
