#include "Spaceship.hpp"
#include <stdexcept>  // For exception handling

// Constants for spaceship scaling and movement factor
constexpr float SCALE_FACTOR = 0.3f;
constexpr float MOVE_FACT = 10.f;

SpaceShip::SpaceShip(sf::Vector2u winSize) : Universe::SpaceObject() {
    if (!texture_.loadFromFile("res/rebel_cruiser.gif")) {
        throw std::runtime_error("Failed to load spaceship texture");
    }
    
    sprite_.setTexture(texture_);
    sprite_.setPosition(static_cast<float>(winSize.x) / 3.f, static_cast<float>(winSize.y) - 100.f);
    sprite_.setScale(SCALE_FACTOR, SCALE_FACTOR);
}

void SpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

void SpaceShip::move(sf::Keyboard::Key direction, sf::Vector2u winSize) {
    sf::Vector2f current = sprite_.getPosition();
    
    switch (direction) {
        case sf::Keyboard::Left:
            current.x -= MOVE_FACT;
            break;
        case sf::Keyboard::Right:
            current.x += MOVE_FACT;
            break;
        case sf::Keyboard::Up:
            current.y -= MOVE_FACT;
            break;
        case sf::Keyboard::Down:
            current.y += MOVE_FACT;
            break;
        default:
            break;
    }

    // Boundary checks to prevent the spaceship from moving out of the window
    const sf::FloatRect bounds = sprite_.getGlobalBounds();
    const float winWidth = static_cast<float>(winSize.x);  // Window width
    const float winHeight = static_cast<float>(winSize.y);  // Window height

    // Check horizontal boundaries (left and right)
    if (current.x < 0) {
        current.x = 0;  // Prevent moving off the left side
    } else if (current.x + bounds.width > winWidth) {
        current.x = winWidth - bounds.width;  // Prevent moving off the right side
    }

    // Check vertical boundaries (top and bottom)
    if (current.y < 0) {
        current.y = 0;  // Prevent moving off the top side
    } else if (current.y + bounds.height > winHeight) {
        current.y = winHeight - bounds.height;  // Prevent moving off the bottom side
    }

    sprite_.setPosition(current);  // Update the position of the sprite
}

