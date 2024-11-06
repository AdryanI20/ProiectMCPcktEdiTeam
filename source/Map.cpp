#include "Map.h"
#include "CellType.h"
#include <iostream>

Map::Map(int rows,int cols): rows(rows),cols(cols){
    grid.resize(rows, std::vector<CellType>(cols, FREE_SPACE));
}

void Map::displayRandomMop() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int randValue = rand() % 3;
            grid[i][j] = static_cast<CellType>(randValue);
        }
    }
}
void Map::displayMap() const{
    for(int i =0;i<rows;++i){
        for(int j =0;j<cols;++j){
            char type;
            switch(grid[i][j]){
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
            std::cout<< type<<" ";
        }
        std::cout<<std::endl;
    }
};
