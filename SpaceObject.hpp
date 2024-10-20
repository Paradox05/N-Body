#ifndef SPACEOBJECT_HPP_
#define SPACEOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <stdexcept>

namespace Universe {

class SpaceObject : public sf::Drawable {
public:

~SpaceObject();

const sf::Vector2f &getLocation() const;

void setLocation(const sf::Vector2f &location);

const sf::Vector2u &getVelocity() const;

void setVelocity(const sf::Vector2u &velocity);

double getMass() const;

void setMass(double mass);
protected:

SpaceObject();

SpaceObject(sf::Vector2f location, sf::Vector2u velocity, double mass);
private:

virtual void draw(sf::RenderTarget &target,
sf::RenderStates states) const = 0;
sf::Vector2f position_;
sf::Vector2u velocity_;
double
mass_;

};
}

#endif