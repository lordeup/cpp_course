#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
sf::Vector2f speed[5] = {{20.f, 80.f}, {30.f, 40.f}, {50.f, 60.f}, {100.f, 10.f}, {70.f, 30.f}};
unsigned int circleColor[5][3] = {{255, 255, 0}, {255, 0, 243}, {0, 255, 255}, {0, 128, 0}, {234, 12, 56}};

void update(std::vector<sf::CircleShape> &circles, sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();
    for (size_t i = 0; i < 5; ++i)
    {
        if ((circles[i].getPosition().x > WINDOW_WIDTH - 40.f) || (circles[i].getPosition().x < 0))
        {
            speed[i].x = -speed[i].x;
        }
        if ((circles[i].getPosition().y > WINDOW_HEIGHT - 40.f) || (circles[i].getPosition().y < 0))
        {
            speed[i].y = -speed[i].y;
        }
        circles[i].setPosition(circles[i].getPosition() + speed[i] * deltaTime);
    }
}
void pollEvents(sf::RenderWindow &window, std::vector<sf::CircleShape> &circles)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<sf::CircleShape> &circles)
{
    window.clear();
    for (size_t i = 0; i < 5; ++i)
    {
        window.draw(circles[i]);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "BALLS", sf::Style::Default, settings);
    sf::Clock clock;
    std::vector<sf::CircleShape> circles;
    for (size_t i = 0; i < 5; ++i)
    {
        circles.push_back(sf::CircleShape(20.f));
        circles[i].setPosition({float(rand() % 700), float(rand() % 500)});
        circles[i].setFillColor(sf::Color(circleColor[i][1], circleColor[i][2], circleColor[i][3]));
    }

    while (window.isOpen())
    {
        pollEvents(window, circles);
        update(circles, clock);
        redrawFrame(window, circles);
    }
}