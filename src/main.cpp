#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct Point{int x,y;};
int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(400,533), "Pibble jump");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/pibble.png");
    t3.loadFromFile("images/jesse-plat.png");

    Sprite sBackground(t1), sPers(t2), sPlat(t3);

   
    
   // sBackground.setTextureRect(IntRect(0,0, window.getSize().x , window.getSize().y));
    //sPers.setPosition(window.getSize().x/2.f - sPers.getGlobalBounds().width/2.f,
     //                 window.getSize().y - sPers.getGlobalBounds().height - 50.f);

    Point plat[20];

    // randomness for platform gen
    for(int i = 0; i < 10;i++){
        plat[i].x = rand()% (int)(window.getSize().x - sPlat.getGlobalBounds().width);
        plat[i].y = rand() % (int)(window.getSize().x - sPlat.getGlobalBounds().height);
    }

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed) window.close();

        }
       window.clear(Color::White);

        window.draw(sBackground);
        window.draw(sPers);
        for(int i =0; i < 10; i++){
            sPlat.setPosition((float)plat[i].x,(float)plat[i].y);
            window.draw(sPlat);
        }
        window.display();
    }

    return 0;
}
