#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void init(sf::ConvexShape &shape)
{
    shape.setPosition({400, 300});
    shape.setPointCount(7);
    shape.setPoint(0, {0, -80});
    shape.setPoint(1, {80, 0});
    shape.setPoint(2, {40, 0});
    shape.setPoint(3, {40, 80});
    shape.setPoint(4, {-40, 80});
    shape.setPoint(5, {-40, 0});
    shape.setPoint(6, {-80, 0});
    shape.setFillColor(sf::Color(255, 255, 0));
    shape.setRotation(10);
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color(0, 0, 0));
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &shape)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(shape);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Yellow arrow", sf::Style::Default, settings);
    sf::ConvexShape shape;

    init(shape);

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
        redrawFrame(window, shape);
    }
}