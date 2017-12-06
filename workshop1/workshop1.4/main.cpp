#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

struct Drawing
{
    sf::Image heroimage;
    sf::Texture herotexture;
    sf::Sprite herosprite;
};
void initcat(Drawing &Cat)
{
    Cat.heroimage.loadFromFile("images/cat.png");
    Cat.herotexture.loadFromImage(Cat.heroimage);
    Cat.herosprite.setTexture(Cat.herotexture);
    Cat.herosprite.setPosition(400, 300);
}

void initdot(Drawing &Dot)
{
    Dot.heroimage.loadFromFile("images/reddot.png");
    Dot.herotexture.loadFromImage(Dot.heroimage);
    Dot.herosprite.setTexture(Dot.herotexture);
    Dot.herosprite.setOrigin(20, 18);
}
sf::Vector2f NormalizeVector(sf::Vector2f vector)
{
    float lenght = sqrt((vector.x * vector.x) + (vector.y * vector.y));
    if (lenght != 0)
    {
        return sf::Vector2f((vector.x / lenght), (vector.y / lenght));
    }
}
void onMousePressed(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

void update(Drawing &Dot, Drawing &Cat, const sf::Vector2f &mousePosition, sf::Clock &clock)
{
    Dot.herosprite.setPosition(mousePosition.x, mousePosition.y);
    sf::Vector2f delta = mousePosition - Cat.herosprite.getPosition();
    float angle = atan2(delta.y, delta.x);
    float deltaTime = clock.restart().asSeconds();
    float speed = 80;
    sf::Vector2f direction = NormalizeVector(delta);
    float u = std::hypot(Dot.herosprite.getPosition().x - Cat.herosprite.getPosition().x, Dot.herosprite.getPosition().y - Cat.herosprite.getPosition().y);
    if ((u > 10) && (mousePosition.x > 0))
    {
        if (Cat.herosprite.getPosition().x <= mousePosition.x)
        {
            Cat.herosprite.setPosition(Cat.herosprite.getPosition() + direction * deltaTime * speed);
            Cat.herosprite.setScale(1, 1);
        }
        else
        {
            Cat.herosprite.setPosition(Cat.herosprite.getPosition() + direction * deltaTime * speed);
            Cat.herosprite.setScale(-1, 1);
        }
    }
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
        case sf::Event::MouseButtonPressed:
            onMousePressed(event.mouseButton, mousePosition);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Drawing &Cat, Drawing &Dot)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(Cat.herosprite);
    window.draw(Dot.herosprite);
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
        "Cat", sf::Style::Default, settings);
    Drawing Cat;
    Drawing Dot;
    initcat(Cat);
    initdot(Dot);
    sf::Vector2f mousePosition = {-100, -100};
    sf::Clock clock;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(Dot, Cat, mousePosition, clock);
        redrawFrame(window, Cat, Dot);
    }
}