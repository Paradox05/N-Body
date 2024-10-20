#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "SpaceObject.hpp"
#include <SFML/Graphics.hpp>

class SpaceShip : public Universe::SpaceObject {
public:
    // Constructor with window size as argument
    explicit SpaceShip(sf::Vector2u winSize);

    // Move the spaceship based on keyboard input and window size
    void move(sf::Keyboard::Key direction, sf::Vector2u winSize);  // Updated signature

private:
    // Override the draw function to render the spaceship
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // Sprite for spaceship
    sf::Sprite sprite_;

    // Texture for spaceship
    sf::Texture texture_;
};

#endif  // SPACESHIP_HPP
