#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;
using namespace sf;

struct Drawing
{
    vector<CircleShape> circles;
    vector<Vector2f> speed;
};

struct PRNG
{
    mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(time(nullptr));
    generator.engine.seed(seed);
}

float getRandomFloat(PRNG &generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);
    uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

Vector2f getRandomPosition(PRNG &generator)
{
    assert(0 < 500);
    uniform_real_distribution<float> distributionX(0, 700);
    float posX = distributionX(generator.engine);
    assert(0 < 500);
    uniform_real_distribution<float> distributionY(0, 500);
    float posY = distributionY(generator.engine);
    return (Vector2f{posX, posY});
}

Color getRandomColor(PRNG &generator)
{
    int color[8][3] = {{51, 255, 153},
                       {255, 204, 0},
                       {204, 255, 255},
                       {102, 0, 255},
                       {102, 204, 0},
                       {204, 0, 0},
                       {204, 204, 255},
                       {255, 204, 204}};
    uniform_real_distribution<float> firstColor(0, 7);
    int first = firstColor(generator.engine);

    uniform_real_distribution<float> secondColor(0, 7);
    int second = secondColor(generator.engine);

    int newColorR = (color[first][1] + color[second][1]) * 0.5;
    int newColorG = (color[first][2] + color[second][2]) * 0.5;
    int newColorB = (color[first][3] + color[second][3]) * 0.5;
    return (Color(newColorR, newColorG, newColorB));
}
void ballsCollision(Drawing &Balls)
{
    for (size_t fi = 0; fi < Balls.circles.size(); ++fi)
    {
        for (size_t si = fi + 1; si < Balls.circles.size(); ++si)
        {
            const Vector2f deltaPos = Balls.circles[fi].getPosition() - Balls.circles[si].getPosition();
            float distance = hypotf(deltaPos.x, deltaPos.y);
            if (distance <= 40)
            {
                Vector2f delta1 = Balls.speed[fi] - Balls.speed[si];
                Vector2f delta2 = Balls.speed[si] - Balls.speed[fi];
                Vector2f delta11 = Balls.circles[fi].getPosition() - Balls.circles[si].getPosition();
                Vector2f delta22 = Balls.circles[si].getPosition() - Balls.circles[fi].getPosition();
                float dot1 = delta1.x * delta11.x + delta1.y * delta11.y;
                float dot2 = delta2.x * delta22.x + delta2.y * delta22.y;
                Balls.speed[fi] = Balls.speed[fi] - (dot1 / (distance * distance)) * delta11;
                Balls.speed[si] = Balls.speed[si] - (dot2 / (distance * distance)) * delta22;
            }
        }
    }
}
void onMousePressed(const Event::MouseButtonEvent &event, Drawing &Balls, PRNG &generator)
{
    Vector2f mousePos = {(float(event.x)), (float(event.y))};
    bool notInCircle = true;
    for (size_t i = 0; i < Balls.circles.size(); ++i)
    {
        Vector2f delta = mousePos - Balls.circles[i].getPosition();
        float distanceBetween = hypot(delta.x, delta.y);
        if (distanceBetween < 50)
        {
            notInCircle = false;
            break;
        }
    }
    if (notInCircle)
    {
        Balls.circles.push_back(CircleShape(20.f));
        Balls.circles.back().setPosition({(float(event.x) - 20),
                                          (float(event.y) - 20)});
        Balls.circles.back().setFillColor(getRandomColor(generator));
        Balls.speed.push_back(Vector2f{getRandomFloat(generator, 0, 100), getRandomFloat(generator, 0, 100)});
    }
}

void pollEvents(RenderWindow &window, Drawing &Balls, PRNG &generator)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseButtonPressed:
            onMousePressed(event.mouseButton, Balls, generator);
            break;
        default:
            break;
        }
    }
}

void update(Drawing &Balls, Clock &clock)
{
    float dt = clock.restart().asSeconds();
    for (size_t i = 0; i < Balls.circles.size(); ++i)
    {
        if ((Balls.circles[i].getPosition().x < 0) || (Balls.circles[i].getPosition().x > 760))
        {
            Balls.speed[i].x = -Balls.speed[i].x;
        }
        if ((Balls.circles[i].getPosition().y < 0) || (Balls.circles[i].getPosition().y > 560))
        {
            Balls.speed[i].y = -Balls.speed[i].y;
        }
        Balls.circles[i].setPosition(Balls.circles[i].getPosition() + Balls.speed[i] * dt);
    }
    ballsCollision(Balls);
}
void redrawFrame(RenderWindow &window, Drawing &Balls)
{
    window.clear(Color::Black);
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

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls", Style::Default, settings);
    Clock clock;
    PRNG generator;
    initGenerator(generator);
    Drawing Balls;
    while (window.isOpen())
    {
        pollEvents(window, Balls, generator);
        update(Balls, clock);
        redrawFrame(window, Balls);
    }
}
