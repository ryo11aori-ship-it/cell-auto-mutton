#include"Automaton.h"
#include<algorithm>
#include<cmath>
using namespace std;
Automaton::Automaton(int size):gridSize(size){
grid.assign(gridSize,vector<Cell>(gridSize));
}
void Automaton::toggleCell(int x,int y){
if(x>=0&&x<gridSize&&y>=0&&y<gridSize){
grid[y][x].isAlive=!grid[y][x].isAlive;
}
}
void Automaton::update(){
// ここに周囲の密度計算と辺の更新処理を書いていきます
}
const vector<vector<Cell>>& Automaton::getGrid()const{
return grid;
}
