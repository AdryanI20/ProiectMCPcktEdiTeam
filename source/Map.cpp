//
// Created by norri on 10/30/2024.
//

#include "Map.h"
#include "CellType.h"
Map::Map(int rows,int cols): rows(rows),cols(cols){
    grid.resize(rows,std::vector<CellType>(cols,FREE_SPACE))
};

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
                int FREE_SPACE=S; break;
                int DESTRUCTIBIL_WALL=W; break;
                int INDESTRUCTIBIL_WALL=I; break;
            }
            std::cout<< type<<" ";
        }
        std::cout<<std::endl;
    }
};
