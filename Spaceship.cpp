#include "Spaceship.hpp"

SpaceShip::SpaceShip(sf::Vector2u winSize) : Universe::SpaceObject() {
  texture_.loadFromFile("res/spaceship.png");
  sprite_.setTexture(texture_);
  sprite_.setPosition(winSize.x/3, winSize.y-100);
  sprite_.setScale(0.3, 0.3);
}

void SpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void SpaceShip::move(sf::Keyboard::Key direction) {
  sf::Vector2f current = sprite_.getPosition();
  switch (direction) {
    case sf::Keyboard::Left:
      current.x -= MOVE_FACT;
      sprite_.setPosition(current);
      break;
    case sf::Keyboard::Right:
      current.x += MOVE_FACT;
      sprite_.setPosition(current);
      break;
    case sf::Keyboard::Up:
      current.y -= MOVE_FACT;
      sprite_.setPosition(current);
      break;
    case sf::Keyboard::Down:
      current.y += MOVE_FACT;
      sprite_.setPosition(current);
      break;
    default:
      break;
  }
}
