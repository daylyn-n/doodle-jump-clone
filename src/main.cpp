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
    t3.loadFromFile("images/platform.png");

    Sprite sBackground(t1), sPers(t2), sPlat(t3);

    Point plat[20];

    float dx = 0;
    float dy = 0;
    int x = 100, y = 100, h =100;

    float playerW = sPers.getGlobalBounds().width;
    float playerH = sPers.getGlobalBounds().height;
    float platW = sPlat.getGlobalBounds().width;
    float platH = sPlat.getGlobalBounds().height;



    // randomness for platform gen
    for(int i = 0; i < 7;i++){
        plat[i].x = rand()% (int)(window.getSize().x - sPlat.getGlobalBounds().width);
        plat[i].y = rand() % (int)(window.getSize().x - sPlat.getGlobalBounds().height + 60);
    }

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed) window.close();
            if(Keyboard::isKeyPressed(Keyboard::D)) {
                x +=6;
            }
            if(Keyboard::isKeyPressed(Keyboard::A)) {
                x -=6;
            }
          

        }
        sPers.setOrigin(sPers.getGlobalBounds().width / 2, 0);
         // Set sprite scale for mirroring
        if (x < 0 || x > window.getSize().x - sPers.getGlobalBounds().width)
            sPers.setScale(-1.f, 1.f); // flip horizontally
        else
            sPers.setScale(1.f, 1.f);  // normal
        
        // always falling
        dy+=0.2;
        y+=dy;
        if(y > 500 ) dy=-10;

        // move screen up to progress
        if(y<h){
            for(int i = 0; i<7 ;i++){
                y = h;
                plat[i].y = plat[i].y -dy;
                if(plat[i].y > window.getSize().y) {
                    plat[i].y = 0; 
                    plat[i].x = rand() % (int)(window.getSize().x - sPlat.getGlobalBounds().width);
                }
            }
        }

        // platform collisoin
        for(int i = 0; i < 7; i++) {
        // Only check if falling
        if (dy > 0) {
            float nextY = y + dy;
            // Check if player is above the platform and will land on it this frame
            // NOTE* previously there was a bug where the sPers sprite would just pass through the platform
            if (
                (x + playerW > plat[i].x) && (x < plat[i].x + platW) &&
                (y + playerH <= plat[i].y) && (nextY + playerH >= plat[i].y)
            ) {
                dy = -10;
                y = plat[i].y - playerH; // Snap player on top of platform
            }
        }
}

        sPers.setPosition(x,y);
        window.draw(sBackground);
        window.draw(sPers);
        for(int i =0; i < 7; i++){
            sPlat.setPosition(plat[i].x,plat[i].y);
            window.draw(sPlat);
        }
        window.display();
    }

    return 0;
}
