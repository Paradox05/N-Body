#include <string>
#include <stdexcept>  // For error handling
#include "body.hpp"
#include "Universe.hpp"

const double G = 6.67e-11;

// Constructor using correct initialization order
Universe::Body::Body(int winSize)
    : x_pos(0), y_pos(0), x_vel(0), y_vel(0), x_accel_(0), y_accel_(0) {
}

// Destructor
Universe::Body::~Body() {}


void Universe::Body::createBodyTexture() {
    if (!pTexture_.loadFromFile(file_name)) {
        throw std::runtime_error("Failed to load texture: " + file_name);
    }
}

void Universe::Body::createBodySprite() {
    pSprite_.setTexture(pTexture_);
}

double Universe::Body::calNetforce(double distance, double m1, double m2) {
    if (distance == 0) {
        throw std::runtime_error("Distance between bodies cannot be zero.");
    }
    return (G * m1 * m2) / (distance * distance);
}

void Universe::Body::updateVelocity(double times) {
    x_vel += x_accel_ * times;
    y_vel -= y_accel_ * times;  // Assuming upward motion decreases y
}

void Universe::Body::step(double times) {
    x_pos += x_vel * times;
    y_pos -= y_vel * times;  // Assuming upward motion decreases y
}

void Universe::Body::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(pSprite_, states);
}

std::string Universe::Body::getPlanetName() const {
    return planet_name_;
}

void Universe::Body::parsePlanetName() {
    std::string parsed_name;
    parsed_name += toupper(planet_name_.at(0));  // Capitalize first letter

    for (size_t i = 1; i < planet_name_.size() && planet_name_.at(i) != '.'; ++i) {
        parsed_name += planet_name_.at(i);  // Copy characters until '.'
    }
    
    planet_name_ = parsed_name;
}
