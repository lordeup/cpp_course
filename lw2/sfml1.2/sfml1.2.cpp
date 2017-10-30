#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({700, 300}), "Name");
    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({135, 15});
    shape1.setRotation(90);
    shape1.setPosition({177, 105});
    shape1.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({80, 15});
    shape2.setRotation(320);
    shape2.setPosition({180, 160});
    shape2.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({100, 15});
    shape3.setRotation(40);
    shape3.setPosition({180, 160});
    shape3.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({135, 15});
    shape4.setRotation(110);
    shape4.setPosition({370, 120});
    shape4.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({135, 15});
    shape5.setRotation(420);
    shape5.setPosition({370, 120});
    shape5.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({72, 15});
    shape6.setRotation(180);
    shape6.setPosition({407, 215});
    shape6.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({135, 15});
    shape7.setRotation(420);
    shape7.setPosition({480, 120});
    shape7.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({135, 15});
    shape8.setRotation(115);
    shape8.setPosition({600, 120});
    shape8.setFillColor(sf::Color(0x94, 0x00, 0xD3));
    window.draw(shape8);

    window.display();

    sf::sleep(sf::seconds(10));
}