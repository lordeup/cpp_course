#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace sf;

struct Drawing
{
    CircleShape circles;
    Vector2f speed;
    float time;
};

struct PRNG
{
    mt19937 engine;
};

bool IsNeedToRemove(Drawing &Circle)
{
    return Circle.time > 0;
}

void initGenerator(PRNG &generator)
{
    const unsigned seed = time(nullptr);
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
    uniform_real_distribution<float> distributionX(0, 700);
    float posX = distributionX(generator.engine);
    uniform_real_distribution<float> distributionY(0, 500);
    float posY = distributionY(generator.engine);
    return (Vector2f{posX, posY});
}

Color getRandomColor(PRNG &generator)
{
    int color[8][3] = {{51, 255, 153},
                       {255, 204, 23},
                       {204, 255, 255},
                       {102, 89, 255},
                       {102, 204, 85},
                       {204, 74, 92},
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

void onMousePressed(const Event::MouseButtonEvent &event, vector<Drawing> &Balls, PRNG &generator)
{
    Drawing Circle;
    Balls.push_back(Circle);
    Balls.back().circles.setPosition({(float(event.x) - 20),
                                      (float(event.y) - 20)});
    Balls.back().circles.setRadius(20.f);
    Balls.back().circles.setFillColor(getRandomColor(generator));
    Balls.back().speed = (Vector2f{getRandomFloat(generator, 0, 100), getRandomFloat(generator, 0, 100)});
    Balls.back().time = -10;
}

void pollEvents(RenderWindow &window, vector<Drawing> &Balls, PRNG &generator)
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

void update(vector<Drawing> &Balls, Clock &clock)
{
    float dt = clock.restart().asSeconds();
    dt = dt * 0.2;
    for (size_t k = 0; k < 5; k++)
    {

        for (size_t i = 0; i < Balls.size(); ++i)
        {
            Balls[i].time = Balls[i].time + dt;
        }
        auto newEnd = remove_if(Balls.begin(), Balls.end(), IsNeedToRemove);
        Balls.erase(newEnd, Balls.end());
        for (size_t i = 0; i < Balls.size(); ++i)
        {

            if ((Balls[i].circles.getPosition().x < 0) || (Balls[i].circles.getPosition().x > 760))
            {
                Balls[i].speed.x = -Balls[i].speed.x;
            }
            if ((Balls[i].circles.getPosition().y < 0) || (Balls[i].circles.getPosition().y > 560))
            {
                Balls[i].speed.y = -Balls[i].speed.y;
            }
            Balls[i].circles.setPosition(Balls[i].circles.getPosition() + Balls[i].speed * dt);
        }
        for (size_t fi = 0; fi < Balls.size(); ++fi)
        {
            for (size_t si = fi + 1; si < Balls.size(); ++si)
            {
                const Vector2f deltaPos = Balls[fi].circles.getPosition() - Balls[si].circles.getPosition();
                float distance = hypotf(deltaPos.x, deltaPos.y);
                if (distance <= 40)
                {
                    Vector2f delta1 = Balls[fi].speed - Balls[si].speed;
                    Vector2f delta2 = Balls[si].speed - Balls[fi].speed;
                    Vector2f delta11 = Balls[fi].circles.getPosition() - Balls[si].circles.getPosition();
                    Vector2f delta22 = Balls[si].circles.getPosition() - Balls[fi].circles.getPosition();
                    float dot1 = delta1.x * delta11.x + delta1.y * delta11.y;
                    float dot2 = delta2.x * delta22.x + delta2.y * delta22.y;
                    Balls[fi].speed = Balls[fi].speed - (dot1 / (distance * distance)) * delta11;
                    Balls[si].speed = Balls[si].speed - (dot2 / (distance * distance)) * delta22;
                }
            }
        }
    }
}
void redrawFrame(RenderWindow &window, vector<Drawing> &Balls)
{
    window.clear(Color::Black);
    for (size_t gi = 0; gi < Balls.size(); ++gi)
    {
        window.draw(Balls[gi].circles);
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
    vector<Drawing> Balls;
    while (window.isOpen())
    {
        pollEvents(window, Balls, generator);
        update(Balls, clock);
        redrawFrame(window, Balls);
    }
}