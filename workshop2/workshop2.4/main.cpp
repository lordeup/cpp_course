// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <iostream>

// int main()
// {
//     srand(time(nullptr));

//     std::vector<sf::CircleShape> circles;
//     std::vector<sf::Vector2f> speed;

//     constexpr unsigned WINDOW_WIDTH = 800;
//     constexpr unsigned WINDOW_HEIGHT = 600;

//     sf::ContextSettings settings;
//     settings.antialiasingLevel = 8;
//     sf::RenderWindow window(
//         sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
//         "Balls", sf::Style::Default, settings);
//     float radius = 20.f;
//     for (size_t i = 0; i < 5; ++i)
//     {
//         circles.push_back(sf::CircleShape(20.f));
//         circles[i].setPosition({float(rand() % 700), float(rand() % 500)});
//         const int color1 = (rand() % 254);
//         const int color2 = (rand() % 254);
//         const int color3 = (rand() % 254);
//         circles[i].setFillColor(sf::Color(color1, color2, color3));
//         speed.push_back(sf::Vector2f{float(rand() % 100),
//                                      float(rand() % 100)});
//     }

//     sf::Clock clock;

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             switch (event.type)
//             {
//             case sf::Event::Closed:
//                 window.close();
//                 break;
//             default:
//                 break;
//             }
//         }
//         window.clear();
//         for (size_t i = 0; i < 5; ++i)
//         {
//             window.draw(circles[i]);
//         }

//         float dt = clock.restart().asSeconds();

//         for (size_t i = 0; i < 5; ++i)
//         {
//             if ((circles[i].getPosition().x > WINDOW_WIDTH - 2 * radius) || (circles[i].getPosition().x < 0))
//             {
//                 speed[i].x = -speed[i].x;
//             }
//             if ((circles[i].getPosition().y > WINDOW_HEIGHT - 2 * radius) || (circles[i].getPosition().y < 0))
//             {
//                 speed[i].y = -speed[i].y;
//             }
//             circles[i].setPosition(circles[i].getPosition() + speed[i] * dt);
//         }
//         window.display();
//     }
// }

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
std::vector<sf::CircleShape> circles;
std::vector<sf::Vector2f> speed;

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
    srand(time(nullptr));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "BALLS", sf::Style::Default, settings);
    sf::Clock clock;
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
        pollEvents(window, circles);
        update(circles, clock);
        redrawFrame(window, circles);
    }
}