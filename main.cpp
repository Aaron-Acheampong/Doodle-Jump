#include <SFML/Graphics.hpp>
#include <time.h>

auto constexpr WIDTH = 400;
auto constexpr HEIGHT = 533;


struct Point
{ 
    int xpos, ypos;
};


int main()
{
    srand(time(0));

    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "Doodle Jump Game App!!!!!!");
    app.setFramerateLimit(60);

    sf::Texture t1,t2,t3;
    t1.loadFromFile("assets/images/background.png");
    t2.loadFromFile("assets/images/platform.png");
    t3.loadFromFile("assets/images/doodle.png");

    sf::Sprite Background(t1), Platform(t2), Doodle(t3);

    Point positions[20];

    // Set start starting platform positions
    for (int i = 0; i < 10; i++)
    {
        positions[i].xpos = rand() % WIDTH;
        positions[i].ypos = rand() % HEIGHT;
    }

      
    int x = 100, y = 100, viewportheight = 200;
    // Rate of change in x and y directions
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        sf::Event e;
        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                app.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 3;

        // Fall and Bounce motion
        dy += 0.2;
        y += dy;
        if (y > 500)  dy = -10;

        // Extend window view space when going up
        if (y < viewportheight)
            for (int i = 0; i < 10; i++)
            {
                y = viewportheight;
                positions[i].ypos = positions[i].ypos - dy;
                if (positions[i].ypos > HEIGHT)
                {
                    positions[i].ypos = 0; positions[i].xpos = rand() % WIDTH;
                }
            }
        // Change target platform when in proximity
        // Bounce on the nearest avalable platform when falling
        for (int i = 0; i < 10; i++)
        {
            if ((x + 50 > positions[i].xpos) && (x + 20 < positions[i].xpos + 68) && (y + 70 > positions[i].ypos) 
                && (y + 70 < positions[i].ypos + 14) && (dy > 0))  dy = -10;
        }


        Doodle.setPosition(x, y);

        app.draw(Background);
        app.draw(Doodle);

        for (int i = 0; i < 10; i++)
        {
            Platform.setPosition(positions[i].xpos, positions[i].ypos);
            app.draw(Platform);
        }

        app.display();
    }

    return EXIT_SUCCESS;
}
