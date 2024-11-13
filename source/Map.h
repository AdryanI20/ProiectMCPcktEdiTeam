#include <vector>
#include "CellType.h"
#include "Direction.h"
#include <string>

class Map {
public:
    Map(int rows,int cols);
    void createRandomMap();
//    std::vector<std::vector<CellType>> getMap();
    std::string getMapString();
    void placePlayer(int playerId, int row, int col);
    bool canMove(int row, int col, Direction direction) ;
private:
    int m_rows, m_cols;
    std::vector<std::vector<CellType>> m_grid;
};
//