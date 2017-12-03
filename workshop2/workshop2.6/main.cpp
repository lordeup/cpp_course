#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Drawing
{
    std::vector<sf::CircleShape> circles;
    std::vector<sf::Vector2f> speed;
    std::vector<float> timer;
};

void update(Drawing &Balls, sf::Clock &clock)
{
    float dt = clock.restart().asSeconds();

    for (size_t i = 0; i < Balls.timer.size(); i++)
    {
        Balls.timer[i] = Balls.timer[i] + dt;
    }
    for (size_t fi = 0; fi < Balls.circles.size(); ++fi)
    {
        if (Balls.timer[fi] > 10)
        {
            Balls.circles.erase(Balls.circles.begin());
            Balls.speed.erase(Balls.speed.begin());
            Balls.timer.erase(Balls.timer.begin());
        }
    }
    for (size_t ti = 0; ti < Balls.circles.size(); ti++)
    {
        if ((Balls.circles[ti].getPosition().x > 800 - 40) || (Balls.circles[ti].getPosition().x < 0))
        {
            Balls.speed[ti].x = -Balls.speed[ti].x;
        }
        if ((Balls.circles[ti].getPosition().y > 600 - 40) || (Balls.circles[ti].getPosition().y < 0))
        {
            Balls.speed[ti].y = -Balls.speed[ti].y;
        }
        Balls.circles[ti].setPosition(Balls.circles[ti].getPosition() + Balls.speed[ti] * dt);
    }
}
void adding(Drawing &Balls)
{
    Balls.circles.push_back(sf::CircleShape(20.f));
    Balls.circles.back().setPosition({float(rand() % 700), float(rand() % 500)});
    Balls.circles.back().setFillColor(sf::Color(float(rand() % 255), float(rand() % 255), float(rand() % 255)));
    Balls.speed.push_back(sf::Vector2f{float(rand() % 100),
                                       float(rand() % 100)});
    Balls.timer.push_back(0);
}
void pollEvents(sf::RenderWindow &window, Drawing &Balls)
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
            adding(Balls);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Drawing &Balls)
{
    window.clear(sf::Color(255, 255, 255));
    for (size_t gi = 0; gi < Balls.circles.size(); ++gi)
    {
        window.draw(Balls.circles[gi]);
    }
    window.display();
}
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls", sf::Style::Default, settings);
    sf::Clock clock;

    Drawing Balls;

    while (window.isOpen())
    {
        pollEvents(window, Balls);
        update(Balls, clock);
        redrawFrame(window, Balls);
    }
}