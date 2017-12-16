#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

struct Eye
{
    ConvexShape white;
    ConvexShape black;
    Vector2f position;
    float rotation = 0;
};

// Переводит полярные координаты в декартовы
Vector2f toEuclidean(float radiusX, float radiusY, float angle)
{
    return {radiusX * cos(angle), radiusY * sin(angle)};
}

// Обновляет состояние глаза
void updateEye(Eye &Eye, const Vector2f &delta, const Vector2f &mousePosition)
{
    const Vector2f RadiusVector = toEuclidean(20, 40, Eye.rotation);
    const Vector2f whiteOffset = {RadiusVector.x, RadiusVector.y};

    if (abs(delta.x) < abs(RadiusVector.x))
    {
        if (abs(delta.y) < abs(RadiusVector.y))
        {
            Eye.white.setPosition(mousePosition);
        }
    }
    else
    {
        Eye.white.setPosition(Eye.position + whiteOffset);
    }
    Eye.black.setPosition(Eye.position);
}

// Инициализирует зрачок
void initWhite(Eye &Eye)
{
    Eye.white.setFillColor(Color(0, 0, 0));

    constexpr int pointCount = 200;
    Vector2f ellipseRadius = {15.f, 20.f};
    Eye.white.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        Vector2f point = {ellipseRadius.x * cos(angle), ellipseRadius.y * sin(angle)};
        Eye.white.setPoint(pointNo, point);
    }
}

// Инициализирует глаз
void initEye(Eye &Eye, const float x, const float y)
{
    Eye.position = {x, y};

    Eye.black.setFillColor(Color(0xFF, 0xFF, 0xFF));

    constexpr int pointCount = 200;
    Vector2f ellipseRadius = {50.f, 100.f};
    Eye.black.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        Vector2f point = {ellipseRadius.x * cos(angle), ellipseRadius.y * sin(angle)};
        Eye.black.setPoint(pointNo, point);
    }
    initWhite(Eye);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const Event::MouseMoveEvent &event, Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(RenderWindow &window, Vector2f &mousePosition)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

// Обновляет зрачки, указывающие на мышь
void update(const Vector2f &mousePosition, Eye &LeftEye, Eye &RightEye)
{
    Vector2f delta = mousePosition - LeftEye.position;
    LeftEye.rotation = atan2(delta.y, delta.x);
    updateEye(LeftEye, delta, mousePosition);

    delta = mousePosition - RightEye.position;
    RightEye.rotation = atan2(delta.y, delta.x);
    updateEye(RightEye, delta, mousePosition);
}

// Рисует и выводит один кадр
void redrawFrame(RenderWindow &window, Eye &LeftEye, Eye &RightEye)
{
    window.clear();
    window.draw(LeftEye.black);
    window.draw(LeftEye.white);
    window.draw(RightEye.black);
    window.draw(RightEye.white);
    window.display();
}

// Программа рисует в окне глаза, у которых зрачки поворачиваются
// вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eye follows mouse", Style::Default, settings);

    Eye LeftEye;
    Eye RightEye;

    Vector2f mousePosition;

    initEye(LeftEye, 300, 300);
    initEye(RightEye, 450, 300);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, LeftEye, RightEye);
        redrawFrame(window, LeftEye, RightEye);
    }
}