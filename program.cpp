#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
int windowWidth=1000;
int windowHeight=800;
int main()
{
    RenderWindow window(VideoMode(windowWidth,windowHeight),"Car racing");
    Texture car,background;
    background.loadFromFile("data/images/map.jpg");
    Sprite sbackground(background);
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sbackground);
        window.display();
    }
    return 0;
}
