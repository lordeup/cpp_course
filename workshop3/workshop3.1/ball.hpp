#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "constants.hpp"

class BallWithName : public sf::Drawable
{
public:
  void init();
  void updateBallElements();

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  sf::ConvexShape ball;
  sf::Clock clock;
  sf::Text name;
  sf::Font font;
  sf::Vector2f speed = startSpeed;
};
