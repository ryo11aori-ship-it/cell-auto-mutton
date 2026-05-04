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
void Automaton::tryAddEdge(int x1,int y1,int x2,int y2){
if(x2<0||x2>=gridSize||y2<0||y2>=gridSize)return;
if(!grid[y1][x1].isAlive||!grid[y2][x2].isAlive)return;
if(grid[y1][x1].r_v<=0||grid[y2][x2].r_v<=0)return;
Edge e={min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2)};
if(edges.find(e)==edges.end()){
edges.insert(e);
grid[y1][x1].d_v++;
grid[y2][x2].d_v++;
grid[y1][x1].r_v--;
grid[y2][x2].r_v--;
}
}
void Automaton::update(){
for(int y=0;y<gridSize;y++){
for(int x=0;x<gridSize;x++){
if(!grid[y][x].isAlive)continue;
int aliveNeighbors=0;
for(int dy=-1;dy<=1;dy++){
for(int dx=-1;dx<=1;dx++){
if(dx==0&&dy==0)continue;
int nx=x+dx,ny=y+dy;
if(nx>=0&&nx<gridSize&&ny>=0&&ny<gridSize&&grid[ny][nx].isAlive)aliveNeighbors++;
}
}
float rho=(float)aliveNeighbors/8.0f;
grid[y][x].c_v=clamp((int)floor(8.0f*rho),1,8);
grid[y][x].r_v=grid[y][x].c_v-grid[y][x].d_v;
}
}
for(int y=0;y<gridSize;y++){
for(int x=0;x<gridSize;x++){
if(!grid[y][x].isAlive)continue;
if(grid[y][x].d_v<=1||grid[y][x].d_v>=grid[y][x].c_v){
grid[y][x].isAlive=false;
}
}
}
set<Edge>nextEdges;
for(int y=0;y<gridSize;y++){
for(int x=0;x<gridSize;x++){
grid[y][x].d_v=0;
}
}
for(const auto& e:edges){
if(grid[e.y1][e.x1].isAlive&&grid[e.y2][e.x2].isAlive){
if(grid[e.y1][e.x1].d_v<grid[e.y1][e.x1].c_v&&grid[e.y2][e.x2].d_v<grid[e.y2][e.x2].c_v){
nextEdges.insert(e);
grid[e.y1][e.x1].d_v++;
grid[e.y2][e.x2].d_v++;
}
}
}
edges=nextEdges;
for(int y=0;y<gridSize;y++){
for(int x=0;x<gridSize;x++){
if(grid[y][x].isAlive){
grid[y][x].r_v=grid[y][x].c_v-grid[y][x].d_v;
}
}
}
for(int y=0;y<gridSize;y++){
for(int x=0;x<gridSize;x++){
tryAddEdge(x,y,x+1,y);
tryAddEdge(x,y,x,y+1);
tryAddEdge(x,y,x-1,y);
tryAddEdge(x,y,x,y-1);
}
}
for(int y=0;y<gridSize;y++){
for(int x=0;x<gridSize;x++){
int dxs[]={1,-1,1,-1},dys[]={1,1,-1,-1};
for(int i=0;i<4;i++){
int nx=x+dxs[i],ny=y+dys[i];
if(nx>=0&&nx<gridSize&&ny>=0&&ny<gridSize){
if(grid[y][nx].isAlive||grid[ny][x].isAlive){
tryAddEdge(x,y,nx,ny);
}
}
}
}
}
}
const vector<vector<Cell>>& Automaton::getGrid()const{return grid;}
const set<Edge>& Automaton::getEdges()const{return edges;}
