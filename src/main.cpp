#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{

    RenderWindow window(VideoMode(1280, 720), "Prgoram!");
    window.setFramerateLimit(60);
    RectangleShape rect;
    
    // declare a variable for the position
    Vector2f rectanglePosition(600,360); // Vector2f is a vector that holds 2 floating point values, just some struct

    rect.setPosition(rectanglePosition);
    rect.setSize(Vector2f(100,100));

    float xVelocity = 0;
    float yVelocity = 0;
    // without this while loop, the window would just close
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) // pollEvent returns true, essentially looping over the event unitl otherwise
        {
            if (event.type == Event::Closed) // this ends the event (application)
                window.close();

            if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

            if(Keyboard::isKeyPressed(Keyboard::Up)){
                rect.move(0,-20);
                yVelocity -=20;
            }
            if(Keyboard::isKeyPressed(Keyboard::Down)){
                rect.move(0,20);
                 yVelocity +=20;
            }
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                rect.move(-20,0);
                xVelocity -=20;
            }
             if(Keyboard::isKeyPressed(Keyboard::Right)){
                 // rect.move(20,0);
                xVelocity +=20;
            }
        }

        //motion

        // bounds checking so it doesnt fly off the screen
        if(rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100) xVelocity *=-1; // look at window size, 100 comes from the rect size
        if(rectanglePosition.y < 0 || rectanglePosition.y > 720 - 100) yVelocity *=-1;

        rectanglePosition.x = xVelocity;
        rectanglePosition.y = yVelocity;
        rect.setPosition(rectanglePosition);




        //render
        window.clear(); // needed

        
        window.draw(rect);
        
        
        window.display(); // needed
    }

   

    return 0;
}
