#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

void onMousePressed(const sf::Event::MouseButtonEvent &event, std::vector<sf::CircleShape> &circles, std::vector<sf::Vector2f> &speed)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    circles.push_back(sf::CircleShape(20.f));
    speed.push_back({float(rand() % 100), float(rand() % 100)});
    circles.back().setPosition({(float(event.x) - 20),
                                (float(event.y) - 20)});
    circles.back().setFillColor(sf::Color(float(rand() % 254), float(rand() % 254), float(rand() % 254)));
}
void update(std::vector<sf::CircleShape> &circles, std::vector<sf::Vector2f> &speed, sf::Clock &clock)
{
    float dt = clock.restart().asSeconds();
    for (size_t i = 0; i < circles.size(); ++i)
    {
        if ((circles[i].getPosition().x > 760) || (circles[i].getPosition().x < 0))
        {
            speed[i].x = -speed[i].x;
        }
        if ((circles[i].getPosition().y > 560) || (circles[i].getPosition().y < 0))
        {
            speed[i].y = -speed[i].y;
        }
        for (size_t fi = 0; fi < circles.size(); ++fi)
        {
            for (size_t si = fi + 1; si < circles.size(); ++si)
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
        circles[i].setPosition(circles[i].getPosition() + speed[i] * dt);
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
        case sf::Event::MouseButtonPressed:
            onMousePressed(event.mouseButton, circles, speed);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<sf::CircleShape> &circles)
{
    window.clear(sf::Color(255, 255, 255));
    for (size_t i = 0; i < circles.size(); ++i)
    {
        window.draw(circles.at(i));
    }
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "BALLS", sf::Style::Default, settings);
    sf::Vector2f mousePosition;
    sf::Clock clock;
    std::vector<sf::CircleShape> circles;
    std::vector<sf::Vector2f> speed;

    while (window.isOpen())
    {
        pollEvents(window, circles, speed);
        update(circles, speed, clock);
        redrawFrame(window, circles);
    }
}