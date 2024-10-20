#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include "SpaceObject.hpp"
#define MOVE_FACT 15

class SpaceShip : public Universe::SpaceObject {
public:
explicit SpaceShip(sf::Vector2u winSize);
void move(sf::Keyboard::Key direction);
private:
virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
sf::Sprite sprite_;
sf::Texture texture_;
};
#endif