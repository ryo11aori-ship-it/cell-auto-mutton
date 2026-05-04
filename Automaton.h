#pragma once
#include<vector>
struct Cell{
bool isAlive=false;
int c_v=0,d_v=0,r_v=0;
};
class Automaton{
public:
Automaton(int size);
void update();
void toggleCell(int x,int y);
const std::vector<std::vector<Cell>>& getGrid()const;
private:
int gridSize;
std::vector<std::vector<Cell>>grid;
};
