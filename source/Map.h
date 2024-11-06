#include <vector>
#include "CellType.h"
#include <string>

class Map {
public:
    Map(int rows,int cols);
    void createRandomMap();
//    std::vector<std::vector<CellType>> getMap();
    std::string getMapString();
private:
    int m_rows, m_cols;
    std::vector<std::vector<CellType>> m_grid;
};