#include<SFML/Graphics.hpp>
#include<SFML/Window/Event.hpp>
#include<optional>
#include<vector>
#include<cmath>
#include"Automaton.h"
using namespace std;
int main(){
const int S=100;
float cs=20.0f;
Automaton aut(S);
sf::RenderWindow window(sf::VideoMode({800,800}),"0-Dim Automaton");
sf::View view=window.getDefaultView();
view.setCenter({(S*cs)/2.0f,(S*cs)/2.0f});
window.setView(view);
bool running=false;
float speed=0.1f;
sf::Clock clock;
bool isDragging=false;
sf::Vector2i oldMousePos;
while(window.isOpen()){
while(const optional<sf::Event> event=window.pollEvent()){
if(event->getIf<sf::Event::Closed>()){
window.close();
}else if(const auto* res=event->getIf<sf::Event::Resized>()){
sf::Vector2f oldCenter=view.getCenter();
view.setSize({(float)res->size.x,(float)res->size.y});
view.setCenter(oldCenter);
window.setView(view);
}else if(const auto* wheel=event->getIf<sf::Event::MouseWheelScrolled>()){
if(wheel->wheel==sf::Mouse::Wheel::Vertical){
float z=(wheel->delta>0)?0.8f:1.25f;
view.zoom(z);
window.setView(view);
}
}else if(const auto* mb=event->getIf<sf::Event::MouseButtonPressed>()){
if(mb->button==sf::Mouse::Button::Left){
sf::Vector2f wPos=window.mapPixelToCoords(mb->position,view);
int gx=(int)round(wPos.x/cs);
int gy=(int)round(wPos.y/cs);
if(gx>=0&&gx<S&&gy>=0&&gy<S){
aut.toggleCell(gx,gy);
}
}else if(mb->button==sf::Mouse::Button::Right){
isDragging=true;
oldMousePos=mb->position;
}
}else if(const auto* mr=event->getIf<sf::Event::MouseButtonReleased>()){
if(mr->button==sf::Mouse::Button::Right)isDragging=false;
}else if(const auto* mm=event->getIf<sf::Event::MouseMoved>()){
if(isDragging){
sf::Vector2f d=window.mapPixelToCoords(oldMousePos,view)-window.mapPixelToCoords(mm->position,view);
view.move(d);
window.setView(view);
oldMousePos=mm->position;
}
}else if(const auto* kp=event->getIf<sf::Event::KeyPressed>()){
if(kp->code==sf::Keyboard::Key::Space)running=!running;
if(kp->code==sf::Keyboard::Key::Up)speed=max(0.01f,speed-0.01f);
if(kp->code==sf::Keyboard::Key::Down)speed+=0.01f;
}
}
if(running&&clock.getElapsedTime().asSeconds()>speed){
aut.update();
clock.restart();
}
window.clear(sf::Color((uint8_t)20,(uint8_t)20,(uint8_t)25));
vector<sf::Vertex> gridLines;
for(int i=0;i<=S;i++){
gridLines.push_back(sf::Vertex{{i*cs,0.0f},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
gridLines.push_back(sf::Vertex{{i*cs,S*cs},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
gridLines.push_back(sf::Vertex{{0.0f,i*cs},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
gridLines.push_back(sf::Vertex{{S*cs,i*cs},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
}
window.draw(gridLines.data(),gridLines.size(),sf::PrimitiveType::Lines);
const auto& g=aut.getGrid();
for(const auto& e : aut.getEdges()){
sf::Vertex line[2]={
sf::Vertex{{e.x1*cs,e.y1*cs},sf::Color((uint8_t)100,(uint8_t)100,(uint8_t)255,(uint8_t)150)},
sf::Vertex{{e.x2*cs,e.y2*cs},sf::Color((uint8_t)100,(uint8_t)100,(uint8_t)255,(uint8_t)150)}
};
window.draw(line,2,sf::PrimitiveType::Lines);
}
for(int y=0;y<S;y++){
for(int x=0;x<S;x++){
if(g[y][x].isAlive){
float r=cs*0.15f;
sf::CircleShape dot(r);
dot.setOrigin({r,r});
dot.setPosition({x*cs,y*cs});
dot.setFillColor(sf::Color::Cyan);
window.draw(dot);
}
}
}
window.display();
}
return 0;
}
