#include <vector>
#include "CellType.h"

class Map {
private:
    int rows, cols;
    std::vector<std::vector<CellType>>grid;
public:
    Map(int rows,int cols);
    void displayRandomMop();
    void displayMap()const;
};