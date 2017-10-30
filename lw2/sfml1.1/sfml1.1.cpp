#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({170, 235}), "title");
    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({80, 230});
    shape1.setPosition({50, 0});
    shape1.setFillColor(sf::Color(0x69, 0x69, 0x69));
    window.draw(shape1);

    sf::CircleShape shape2(35);
    shape2.setPosition({55, 5});
    shape2.setFillColor(sf::Color(0x00, 0xFF, 0x00));
    window.draw(shape2);

    sf::CircleShape shape3(35);
    shape3.setPosition({55, 80});
    shape3.setFillColor(sf::Color(0xFF, 0x45, 0x00));
    window.draw(shape3);

    sf::CircleShape shape4(35);
    shape4.setPosition({55, 160});
    shape4.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}