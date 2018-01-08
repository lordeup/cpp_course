#include "main.hpp"

using namespace std;
using namespace sf;

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

void onMouseMove(Event::MouseMoveEvent &event, Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
    Vector2f distance = Vector2f{WINDOW_WIDTH / 2 - mousePosition.x, WINDOW_HEIGHT / 2 - mousePosition.y};
    float length = sqrt(pow(distance.x, 2.0) + pow(distance.y, 2.0));
    cout << "length: " << length << endl;
}

void redrawFrame(RenderWindow &window, VertexArray(&lines))
{
    window.clear(Color(0, 0, 0));
    window.draw(lines);
    window.display();
}

void developLine(VertexArray(&line), Vector2f mousePosition)
{
    line[0].position = mousePosition;
    line[1].position = Vector2f(400, 300);

    line[0].color = Color(0, 0, 255);
    line[1].color = Color(0, 0, 255);
}

int main()
{
    VertexArray line(Lines, 2.0);

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The line between the center of the window and the cursor");

    Vector2f mousePosition;

    while (window.isOpen())
    {
        developLine(line, mousePosition);
        pollEvents(window, mousePosition);
        redrawFrame(window, line);
    }
}