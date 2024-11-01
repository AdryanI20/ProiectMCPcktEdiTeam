//
// Created by norri on 10/30/2024.
//

#ifndef PROIECTMC_MAP_H
#define PROIECTMC_MAP_H


class Map {
private:
    int rows, cols;
    std::vector<std::vector<CellType>>grid;
public:
    Map(int rows,int cols);
    void displayRandomMop();
    void displayMap()const;
};


#endif //PROIECTMC_MAP_H
