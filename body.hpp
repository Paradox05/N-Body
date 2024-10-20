#ifndef BODY_HPP_
#define BODY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "SpaceObject.hpp"
#include "NonCopyClass.hpp"

namespace Universe {

class Body : public SpaceObject, virtual private NonCopyClass {
public:
    // Constructor and Destructor
    explicit Body(int window_size);
    ~Body();

    // Physics-related functions
    void step(double times);
    double calNetforce(double radius, double planet1_mass, double planet2_mass);
    void updateVelocity(double times);

    // Setters and Getters for velocity
    void set_xVel(double xvel) { x_vel = xvel; }
    void set_yVel(double yvel) { y_vel = yvel; }
    double get_xVel() const { return x_vel; }
    double get_yVel() const { return y_vel; }

    // Setters and Getters for position
    void set_xPos(double x) { x_pos = x; }
    void set_yPos(double y) { y_pos = y; }
    double get_xPos() const { return x_pos; }
    double get_yPos() const { return y_pos; }

    // Time management
    void setTimes(double times) { times_ = times; }
    double getTimes() const { return times_; }

    // Setters and Getters for mass
    void setMass(double mass) { mass_ = mass; }
    double getMass() const override { return mass_; }

    // Texture and sprite management
    void setBodyTexture(const sf::Texture& texture) { pTexture_ = texture; }
    void createBodyTexture();
    void createBodySprite();
    void setBodySprite(const sf::Sprite& sprite) { pSprite_ = sprite; }
    const sf::Sprite& getSprite() const { return pSprite_; }
    const sf::Texture& getBodyTexture() const { return pTexture_; }

    // Force and acceleration
    double getNetForce() const { return netForce_; }
    const sf::Vector2f& getAcceleration() const { return acceleration_; }
    const sf::Vector2f& getPosition() const { return pSprite_.getPosition(); }

    // Planet name management
    std::string getPlanetName() const;
    std::string getBodyName() const { return planet_name_; }

    // Set acceleration
    void setAcceleration(double x_accel, double y_accel) {
        x_accel_ = x_accel;
        y_accel_ = y_accel;
        acceleration_ = sf::Vector2f(x_accel, y_accel);
    }

    // Set sprite position
    void setSpritePosition(double x, double y) {
        pSprite_.setPosition(sf::Vector2f(x, y));
    }

    // Get initial scale
    sf::Vector2f getInitScale() const {
        return sf::Vector2f(x_pos, y_pos);
    }

    // Drawing the body
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Stream operator overloading for input/output
    friend std::ostream& operator<<(std::ostream& out_stream, const Universe::Body& body) {
        out_stream << body.x_pos << " " << body.y_pos << " " 
                   << body.x_vel << " " << body.y_vel << " "
                   << body.mass_ << " " << body.file_name << " ";
        return out_stream;
    }

    friend std::istream& operator>>(std::istream& in_stream, Universe::Body& body) {
        in_stream >> body.x_pos >> body.y_pos >> body.x_vel >> body.y_vel >> body.mass_;
        std::string image_name;
        in_stream >> image_name;
        body.planet_name_ = image_name;
        body.parsePlanetName();
        body.file_name = "res/" + image_name;
        if (!body.pTexture_.loadFromFile(body.file_name)) {
            throw std::runtime_error("Failed to load texture: " + body.file_name);
        }
        body.pSprite_.setTexture(body.pTexture_);
        return in_stream;
    }

    // Parse planet name
    void parsePlanetName();

private:
    //int wSize_;                       // Window size
    double times_;                    // Time step
    sf::Texture pTexture_;            // Texture for the body
    sf::Sprite pSprite_;              // Sprite for the body
    sf::Vector2f acceleration_;       // Acceleration vector
    double x_pos, y_pos, x_vel, y_vel, mass_; // Position, velocity, mass
    double x_accel_, y_accel_;        // Acceleration components
    std::string file_name;            // File name of the texture
    std::string planet_name_;         // Name of the planet
    double netForce_;                 // Net force on the body
};

}  // namespace Universe

#endif  // BODY_HPP_
