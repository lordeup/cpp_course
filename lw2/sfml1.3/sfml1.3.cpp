#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 600}), "Convex Shapes");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({500, 300});
    shape1.setPosition({200, 300});
    shape1.setFillColor(sf::Color(0x3D, 0x2B, 0x1F));
    window.draw(shape1);

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0xCC, 0x00, 0x00));
    trapeze.setPosition({450, 180});
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {-100, 0});
    trapeze.setPoint(1, {+100, 0});
    trapeze.setPoint(2, {+290, 140});
    trapeze.setPoint(3, {-290, 140});
    window.draw(trapeze);

    sf::RectangleShape shape2;
    shape2.setSize({40, 90});
    shape2.setPosition({520, 140});
    shape2.setFillColor(sf::Color(0xD2, 0xB4, 0x8C));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({70, 170});
    shape3.setPosition({250, 450});
    shape3.setFillColor(sf::Color(0x3B, 0x44, 0x4B));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({70, 50});
    shape4.setPosition({505, 120});
    shape4.setFillColor(sf::Color(0xD2, 0xB4, 0x8C));
    window.draw(shape4);

    sf::CircleShape shape5(18);
    shape5.setPosition({540, 85});
    shape5.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape5);

    sf::CircleShape shape6(20);
    shape6.setPosition({555, 60});
    shape6.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape6);

    sf::CircleShape shape7(25);
    shape7.setPosition({565, 30});
    shape7.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape7);

    sf::CircleShape shape8(28);
    shape8.setPosition({575, 10});
    shape8.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape8);

    window.display();

    sf::sleep(sf::seconds(5));
}