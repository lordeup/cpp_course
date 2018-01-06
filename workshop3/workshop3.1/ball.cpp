#include "ball.hpp"
#include "constants.hpp"

void BallWithName::init()
{
    int pointCount = 200;
    ball.setPosition(startPosition);
    ball.setFillColor(sf::Color(255, 255, 0));
    ball.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float nameRadius = 100;
        sf::Vector2f point = sf::Vector2f{nameRadius * std::sin(angle), nameRadius * std::cos(angle)};
        ball.setPoint(pointNo, point);
    }
    ball.setOutlineThickness(outlineThickness);
    ball.setOutlineColor(sf::Color(0, 0, 255));

    font.loadFromFile("arial.ttf");
    name.setFont(font);
    name.setCharacterSize(fontSize);
    name.setFillColor(sf::Color(0, 0, 0));
    name.setString("Andrey");
    name.setPosition(startName);
}

void BallWithName::updateBallElements()
{
    float dt = clock.restart().asSeconds();
    speed.y = speed.y + (g * dt);
    float x = ball.getPosition().x + speed.x * dt;
    float y = ball.getPosition().y + speed.y * dt;
    ball.setPosition({x, y});
    name.setPosition({(x - deltaNameX), (y - deltaNameY)});

    if ((ball.getPosition().y > (WINDOW_HEIGHT - radiusCircle - outlineThickness)) || (ball.getPosition().y < radiusCircle + outlineThickness))
    {
        speed.y = -speed.y;
    }
    if ((ball.getPosition().x > WINDOW_WIDTH - radiusCircle - outlineThickness) || (ball.getPosition().x < 110))
    {
        speed.x = -speed.x;
    }
}

void BallWithName::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ball, states);
    target.draw(name, states);
}