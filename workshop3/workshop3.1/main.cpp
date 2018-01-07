#include "ball.hpp"
#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <string>

void initWindow(sf::RenderWindow &window)
{
    sf::VideoMode videoMode(800, 600);
    const std::string title = "Name ball";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, title, sf::Style::Default, settings);
}

int main()
{
    sf::RenderWindow window;
    initWindow(window);
    BallWithName Name;
    Name.init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color(255, 255, 255));
        Name.updateBallElements();
        window.draw(Name);
        window.display();
    }
}