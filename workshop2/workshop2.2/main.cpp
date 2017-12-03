#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr size_t SIZE = 5;
float radius = 20.f;

void update(std::vector<sf::CircleShape> &circles, std::vector<sf::Vector2f> &speed, sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();
    for (size_t i = 0; i < 5; ++i)
    {
        if ((circles[i].getPosition().x > WINDOW_WIDTH - 2 * radius) || (circles[i].getPosition().x < 0))
        {
            speed[i].x = -speed[i].x;
        }
        if ((circles[i].getPosition().y > WINDOW_HEIGHT - 2 * radius) || (circles[i].getPosition().y < 0))
        {
            speed[i].y = -speed[i].y;
        }
        for (size_t fi = 0; fi < SIZE; ++fi)
        {
            for (size_t si = fi + 1; si < SIZE; ++si)
            {
                const sf::Vector2f deltaPos = circles[fi].getPosition() - circles[si].getPosition();
                float distance = std::hypotf(deltaPos.x, deltaPos.y);
                if (distance <= 39)
                {
                    sf::Vector2f delta1 = speed[fi] - speed[si];
                    sf::Vector2f delta2 = speed[si] - speed[fi];
                    sf::Vector2f delta11 = circles[fi].getPosition() - circles[si].getPosition();
                    sf::Vector2f delta22 = circles[si].getPosition() - circles[fi].getPosition();
                    float dot1 = delta1.x * delta11.x + delta1.y * delta11.y;
                    float dot2 = delta2.x * delta22.x + delta2.y * delta22.y;
                    speed[fi] = speed[fi] - (dot1 / (distance * distance)) * delta11;
                    speed[si] = speed[si] - (dot2 / (distance * distance)) * delta22;
                }
            }
        }
        circles[i].setPosition(circles[i].getPosition() + speed[i] * deltaTime);
    }
}
void pollEvents(sf::RenderWindow &window, std::vector<sf::CircleShape> &circles, std::vector<sf::Vector2f> &speed)
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
    srand(time(nullptr));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "BALLS", sf::Style::Default, settings);
    sf::Clock clock;
    std::vector<sf::CircleShape> circles;
    std::vector<sf::Vector2f> speed;
    for (size_t i = 0; i < 5; ++i)
    {
        circles.push_back(sf::CircleShape(20.f));
        circles[i].setPosition({float(rand() % 700), float(rand() % 500)});
        const int color1 = (rand() % 254);
        const int color2 = (rand() % 254);
        const int color3 = (rand() % 254);
        circles[i].setFillColor(sf::Color(color1, color2, color3));
        speed.push_back(sf::Vector2f{float(rand() % 100),
                                     float(rand() % 100)});
    }
    while (window.isOpen())
    {
        pollEvents(window, circles, speed);
        update(circles, speed, clock);
        redrawFrame(window, circles);
    }
}