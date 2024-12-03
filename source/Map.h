#include <vector>
#include "CellType.h"
#include <string>

class Map {
public:
    Map(int rows,int cols);
    void createRandomMap();
    void createPath(std::pair<int, int> start, std::pair<int, int> finish);
    std::vector<CellType> getNeighboursVal(int X, int Y);
    //std::string getMapString();
    const std::vector<std::vector<CellType>>& getMap();
    void setPositionValue(int X, int Y, CellType value);
    CellType getPositionValue(int X, int Y);
    std::pair<int, int> getSize();
private:
    int m_rows, m_cols;
    std::vector<std::vector<CellType>> m_grid;
};
