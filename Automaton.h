#pragma once
#include<vector>
#include<set>
struct Edge{
int x1,y1,x2,y2;
bool operator<(const Edge& other)const{
if(x1!=other.x1)return x1<other.x1;
if(y1!=other.y1)return y1<other.y1;
if(x2!=other.x2)return x2<other.x2;
return y2<other.y2;
}
};
struct Cell{
bool isAlive=false;
int c_v=0;
int d_v=0;
int r_v=0;
};
class Automaton{
public:
Automaton(int size);
void update();
void toggleCell(int x,int y);
const std::vector<std::vector<Cell>>& getGrid()const;
const std::set<Edge>& getEdges()const;
private:
int gridSize;
std::vector<std::vector<Cell>>grid;
std::set<Edge>edges;
void tryAddEdge(int x1,int y1,int x2,int y2);
};
