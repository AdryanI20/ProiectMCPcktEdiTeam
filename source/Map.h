#include <vector>
#include "CellType.h"
#include "Direction.h"
#include "Character.h"
#include <string>

class Map {
public:
    Map(int rows,int cols);
    void createRandomMap();
    void createPath(std::pair<int, int> start, std::pair<int, int> finish);
//    std::vector<std::vector<CellType>> getMap();
    std::string getMapString();
    void placePlayer(int playerId, int row, int col);
    bool canMove(int row, int col, Direction direction) ;
    void placeCharactersInCorners(std::vector<Character>& characters);
    CellType getPosition(int i, int j);
    void manageCollision(int i, int j);

    void setPositionValue(int X, int Y, CellType value);
    CellType getPositionValue(int X, int Y);
    std::pair<int, int> getSize();
    void clearSurroundingsAroundPlayers();
private:
    int m_rows, m_cols;
    std::vector<std::vector<CellType>> m_grid;
};
//