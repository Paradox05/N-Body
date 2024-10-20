#include "SpaceObject.hpp"

Universe::SpaceObject::SpaceObject() : sf::Drawable() {
}

Universe::SpaceObject::SpaceObject(sf::Vector2f location,
                                   sf::Vector2u velocity,
                                   double mass) : sf::Drawable() {
}

Universe::SpaceObject::~SpaceObject() {
}

const sf::Vector2f& Universe::SpaceObject::getLocation() const {
  return position_;
}

void Universe::SpaceObject::setLocation(const sf::Vector2f &location) {
  position_ = location;
}

double Universe::SpaceObject::getMass() const {
  return mass_;
}

void Universe::SpaceObject::setMass(double mass) {
  if (mass <= 0) throw std::runtime_error("Mass must greater than 0");
  mass_ = mass;
}

const sf::Vector2u& Universe::SpaceObject::getVelocity() const {
  return velocity_;
}

void Universe::SpaceObject::setVelocity(const sf::Vector2u &velocity) {
  velocity_ = velocity;
}
