#include<SFML/Graphics.hpp>
#include"Automaton.h"
using namespace std;
int main(){
const int W=800;
const int S=100;
float cs=(float)W/S;
Automaton aut(S);
sf::RenderWindow window(sf::VideoMode(W,W),"0-Dim Automaton");
bool running=false;
float speed=0.1f;
sf::Clock clock;
while(window.isOpen()){
sf::Event event;
while(window.pollEvent(event)){
if(event.type==sf::Event::Closed)window.close();
if(event.type==sf::Event::MouseButtonPressed){
int gx=(int)(event.mouseButton.x/cs);
int gy=(int)(event.mouseButton.y/cs);
aut.toggleCell(gx,gy);
}
if(event.type==sf::Event::KeyPressed){
if(event.key.code==sf::Keyboard::Space)running=!running;
if(event.key.code==sf::Keyboard::Up)speed=max(0.01f,speed-0.01f);
if(event.key.code==sf::Keyboard::Down)speed+=0.01f;
}
}
if(running&&clock.getElapsedTime().asSeconds()>speed){
aut.update();
clock.restart();
}
window.clear(sf::Color(20,20,25));
const auto& g=aut.getGrid();
for(const auto& e : aut.getEdges()){
sf::Vertex line[]={
sf::Vertex(sf::Vector2f(e.x1*cs,e.y1*cs),sf::Color(100,100,255,150)),
sf::Vertex(sf::Vector2f(e.x2*cs,e.y2*cs),sf::Color(100,100,255,150))
};
window.draw(line,2,sf::Lines);
}
for(int y=0;y<S;y++){
for(int x=0;x<S;x++){
if(g[y][x].isAlive){
sf::CircleShape dot(2.0f);
dot.setOrigin(1.0f,1.0f);
dot.setPosition(x*cs,y*cs);
dot.setFillColor(sf::Color::Cyan);
window.draw(dot);
}
}
}
window.display();
}
return 0;
}
