#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

struct Eye
{
    sf::ConvexShape white; // Белый зразок
    sf::ConvexShape black; // Черный зразок
    sf::Vector2f position;
    float rotation = 0;
};

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float x, float y, float angle)
{
    return {x * cos(angle), y * sin(angle)};
}

// Обновляет позиции и повороты частей глаз
void updateEyeElements(Eye &lEye, Eye &rEye)
{
    const sf::Vector2f rotation = {40.f, 60.f};
    const sf::Vector2f whitelEyeOffset = toEuclidean(rotation.x, rotation.y, lEye.rotation);
    const sf::Vector2f whiterEyeOffset = toEuclidean(rotation.x, rotation.y, rEye.rotation);
    lEye.black.setPosition(lEye.position + whitelEyeOffset);
    rEye.black.setPosition(rEye.position + whiterEyeOffset);
}
// Инициализирует глаза
void initEye(Eye &lEye, Eye &rEye)
{
    lEye.position = {300, 350};
    rEye.position = {500, 350};
    sf::Vector2f whiteRadius = {90.f, 170.f};
    sf::Vector2f blackRadius = {20.f, 30.f};
    float pointCount = 100;

    lEye.white.setFillColor(sf::Color(255, 255, 255));
    lEye.white.setPointCount(pointCount);
    lEye.white.setPosition(lEye.position);
    rEye.white.setFillColor(sf::Color(255, 255, 255));
    rEye.white.setPointCount(pointCount);
    rEye.white.setPosition(rEye.position);

    lEye.black.setPointCount(pointCount);
    lEye.black.setFillColor(sf::Color(0, 0, 0));
    lEye.black.setPosition(lEye.position);
    rEye.black.setPointCount(pointCount);
    rEye.black.setFillColor(sf::Color(0, 0, 0));
    rEye.black.setPosition(rEye.position);
    for (float pointEye = 0; pointCount > pointEye; ++pointEye)
    {
        float angle = float(2 * M_PI * pointEye) / float(pointCount);
        sf::Vector2f point = {
            whiteRadius.x * sin(angle),
            whiteRadius.y * cos(angle)};
        lEye.white.setPoint(pointEye, point);
        rEye.white.setPoint(pointEye, point);
    }

    for (float pointEye = 0; pointCount > pointEye; ++pointEye)
    {
        float angle = float(2 * M_PI * pointEye) / float(pointCount);
        sf::Vector2f point = {
            blackRadius.x * sin(angle),
            blackRadius.y * cos(angle)};
        lEye.black.setPoint(pointEye, point);
        rEye.black.setPoint(pointEye, point);
    }

    updateEyeElements(lEye, rEye);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
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

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Eye &lEye, Eye &rEye)
{
    const sf::Vector2f lEyedelta = mousePosition - lEye.position;
    lEye.rotation = atan2(lEyedelta.y, lEyedelta.x);
    const sf::Vector2f rEyedelta = mousePosition - rEye.position;
    rEye.rotation = atan2(rEyedelta.y, rEyedelta.x);
    updateEyeElements(lEye, rEye);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &lEye, Eye &rEye)
{
    window.clear();
    window.draw(lEye.white);
    window.draw(lEye.black);
    window.draw(rEye.white);
    window.draw(rEye.black);
    window.display();
}

// Программа рисует в окне глаза, которые поворачиваются вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eye follows mouse", sf::Style::Default, settings);

    Eye lEye;
    Eye rEye;
    sf::Vector2f mousePosition;

    initEye(lEye, rEye);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, lEye, rEye);
        redrawFrame(window, lEye, rEye);
    }
}