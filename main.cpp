#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace sf;
float windowWidth=1200;
float windowHeight=810;

class mapCLass{

public :
    float xpos;
    float ypos;
    Sprite image;
    mapCLass(float xpos,float ypos,Sprite sprite)
    {
        image=sprite;
        image.setPosition(0,0);
        //image.setScale(1,1);

        }

};


class carClass
{
    public :
        bool onGround;
        float speed;
        float acc; float dec;
        float angle;
        float turnSpeed;
        float maxSpeed;
        float xpos;
        float yvel,xvel;
        float ypos;
        Sprite image;
        bool carFaceRight;

         carClass(Sprite sprite)
         {
              speed=0;
            acc=0.2; dec=1;
            angle=0;
            turnSpeed=0.3;
            maxSpeed=40.0;
            xpos=0;
            ypos=0;
            xvel=0;
            yvel=0;


             image = sprite;
              image.setScale(1,1);
             image.setPosition(100,100);
          //   cout<<"the constructor is called here of carClass";

         }

         void update(bool carLeft,bool carRight,bool carUp,bool carDown)
         {
             if(carUp && speed<maxSpeed)
             {
                if(speed<0)
                    speed+=dec;
                else
                    speed+=acc;
                    xvel+=speed;
             }
             if(carDown && speed>(-maxSpeed))
             {
                 if (speed > 0){

                 speed -= dec;
                 }
                 else{
                 speed -= acc;
                 }
                  xvel+=speed;
             }
             if(!(carUp )&& !(carDown))
                {
                     if (speed - dec > 0) speed -= dec;
                     else if (speed + dec < 0) speed += dec;
                     else speed = 0;
                }

             if((carRight) && speed!=0)
             {

                 angle+=turnSpeed * speed/maxSpeed;

                    xvel=0;

             }
             if((carLeft)&& speed!=0)
             {
                 angle-= turnSpeed * speed/maxSpeed;
                xvel=0;
             }

             speed=speed;
             angle=angle;
         }
};
int main()
{
    RenderWindow window(VideoMode(windowWidth,windowHeight),"this is title of my main window");//created the main window of game
    window.setFramerateLimit(10);
    Texture manTexture;
    manTexture.loadFromFile("data/images/man.png");
    Sprite manSprite(manTexture);
    Font conolasFont;

    Texture carTexture1;
    carTexture1.loadFromFile("data/images/car23.png");
    Sprite carSprite1(carTexture1);

    Texture platfrmSpriteSheet;
    platfrmSpriteSheet.loadFromFile("data/images/map.jpg");
    Sprite earthSpriteSheet(platfrmSpriteSheet);

    carClass carObj(carSprite1);
    mapCLass mapObj(0,0,earthSpriteSheet);
    cout<<carObj.xpos<<carObj.ypos<<endl;
    int offsetX=0,offsetY=0;
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed)
                window.close();
        }
        bool carUp, carDown, carLeft, carRight = false;

        if(Keyboard::isKeyPressed(Keyboard::Right)) carRight = true;
        if(Keyboard::isKeyPressed(Keyboard::Left)) carLeft = true;
        if(Keyboard::isKeyPressed(Keyboard::Up)) carUp = true;
        if(Keyboard::isKeyPressed(Keyboard::Down)) carDown = true;
        if(!Keyboard::isKeyPressed(Keyboard::Right)) carRight = false;
        if(!Keyboard::isKeyPressed(Keyboard::Left)) carLeft = false;
        if(!Keyboard::isKeyPressed(Keyboard::Up)) carUp = false;
        if(!Keyboard::isKeyPressed(Keyboard::Down)) carDown = false;

        carObj.update(carLeft,carRight,carUp,carDown);
        window.clear();
        window.draw(mapObj.image);



       // cout<<carObj.xpos<<carObj.ypos;

        carObj.xpos=carObj.image.getPosition().x;
             carObj.ypos=carObj.image.getPosition().y;
             if(carObj.xpos>1150)
             {
                 carObj.speed=0.5;
             }
             if(carObj.ypos>500)
                carObj.speed=0.5;
                carObj.xvel = sin(carObj.angle) * carObj.speed;
                carObj.yvel = cos(carObj.angle) * carObj.speed;
        carObj.image.setRotation(carObj.angle*180/3.141593);
        carObj.image.move(carObj.xvel,carObj.yvel);

        window.draw(carObj.image);
        window.display();
    }
    return 0;
}
