#include "SpaceObject.hpp"
#include <stdexcept>  // For exception handling

// Default constructor
Universe::SpaceObject::SpaceObject() 
    : sf::Drawable(), position_(0, 0), velocity_(0, 0), mass_(1.0) {  // Default mass is set to 1.0
}

// Parameterized constructor
Universe::SpaceObject::SpaceObject(sf::Vector2f location, sf::Vector2u velocity, double mass)
    : sf::Drawable(), position_(location), velocity_(velocity), mass_(mass) {
    if (mass <= 0) {
        throw std::runtime_error("Mass must be greater than 0");
    }
}

// Destructor
Universe::SpaceObject::~SpaceObject() {
}

// Getter for position
const sf::Vector2f& Universe::SpaceObject::getLocation() const {
    return position_;
}

// Setter for position
void Universe::SpaceObject::setLocation(const sf::Vector2f &location) {
    position_ = location;
}

// Getter for mass
double Universe::SpaceObject::getMass() const {
    return mass_;
}

// Setter for mass with error handling
void Universe::SpaceObject::setMass(double mass) {
    if (mass <= 0) {
        throw std::runtime_error("Mass must be greater than 0");
    }
    mass_ = mass;
}

// Getter for velocity
const sf::Vector2u& Universe::SpaceObject::getVelocity() const {
    return velocity_;
}

// Setter for velocity
void Universe::SpaceObject::setVelocity(const sf::Vector2u &velocity) {
    velocity_ = velocity;
}
