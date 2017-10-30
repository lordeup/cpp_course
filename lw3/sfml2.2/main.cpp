#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;

    const sf::Vector2f ellipseRadius = {200.f, 160.f};
    float amplitude = 100.f;
    constexpr float period = 3;
    const sf::Vector2f position{350, 300};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Polar Rose",
        sf::Style::Default, settings);

    sf::Clock clock;
    sf::ConvexShape ellipse;
    ellipse.setPosition({350, 300});
    ellipse.setFillColor(sf::Color(0x23, 0xE9, 0x01));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = 200 * std::sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{
            radius * std::sin(angle),
            radius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

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
        float wavePhase = clock.getElapsedTime().asSeconds() * float(2 * M_PI);
        float y = amplitude * std::sin(wavePhase / period);
        float x = amplitude * std::cos(wavePhase / period);
        sf::Vector2f offset = {x, y};

        ellipse.setPosition(position + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}
