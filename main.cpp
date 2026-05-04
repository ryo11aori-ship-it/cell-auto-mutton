#include<SFML/Graphics.hpp>
#include<SFML/Window/Event.hpp>
#include<optional>
#include<vector>
#include<cmath>
#include"Automaton.h"
using namespace std;
int main(){
const unsigned int W=800;
const int S=100;
float cs=(float)W/S;
Automaton aut(S);
sf::RenderWindow window(sf::VideoMode({W,W}),"0-Dim Automaton");
bool running=false;
float speed=0.1f;
sf::Clock clock;
while(window.isOpen()){
while(const optional<sf::Event> event=window.pollEvent()){
if(event->getIf<sf::Event::Closed>()){
window.close();
}else if(const auto* mb=event->getIf<sf::Event::MouseButtonPressed>()){
if(mb->button==sf::Mouse::Button::Left){
sf::Vector2f worldPos=window.mapPixelToCoords(mb->position);
int gx=(int)round(worldPos.x/cs);
int gy=(int)round(worldPos.y/cs);
if(gx>=0&&gx<S&&gy>=0&&gy<S){
aut.toggleCell(gx,gy);
}
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
gridLines.push_back(sf::Vertex{{i*cs,(float)W},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
gridLines.push_back(sf::Vertex{{0.0f,i*cs},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
gridLines.push_back(sf::Vertex{{(float)W,i*cs},sf::Color((uint8_t)50,(uint8_t)50,(uint8_t)50)});
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
sf::CircleShape dot(3.0f);
dot.setOrigin({1.5f,1.5f});
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
