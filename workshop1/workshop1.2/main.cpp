#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

void init(sf::ConvexShape &shape)
{
    shape.setPosition({400, 300});
    shape.setPointCount(7);
    shape.setPoint(0, {0, 80});
    shape.setPoint(1, {80, 0});
    shape.setPoint(2, {0, -80});
    shape.setPoint(3, {0, -40});
    shape.setPoint(4, {-80, -40});
    shape.setPoint(5, {-80, 40});
    shape.setPoint(6, {0, 40});
    shape.setFillColor(sf::Color(255, 255, 0));
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color(0, 0, 0));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float &deltaTime)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float maxAngulerSpeed = 90;
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = maxAngulerSpeed * deltaTime;
    const float rotation = abs((angle - pointer.getRotation()));
    sf::Vector2f direction = (1 / hypotf(delta.x, delta.y)) * delta;
    float speed = 80.f;
    if (hypotf(delta.x, delta.y) != 0.f)
    {
        pointer.setPosition(pointer.getPosition() + direction * deltaTime * speed);
    }
    if (angle < pointer.getRotation())
    {
        if ((angle + 180) < pointer.getRotation())
        {
            pointer.setRotation(pointer.getRotation() + min(maxRotation, rotation));
        }
        else
        {
            pointer.setRotation(pointer.getRotation() - min(maxRotation, rotation));
        }
    }
    else
    {
        if ((angle - 180) > pointer.getRotation())
        {
            pointer.setRotation(pointer.getRotation() - min(maxRotation, rotation));
        }
        else
        {
            pointer.setRotation(pointer.getRotation() + min(maxRotation, rotation));
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(pointer);
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
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::Clock clock;
    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    sf::Vector2f direction;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, pointer, deltaTime);
        redrawFrame(window, pointer);
    }
}