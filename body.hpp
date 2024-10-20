#ifndef BODY_HPP_
#define BODY_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "SpaceObject.hpp"
#include "NonCopyClass.hpp"

namespace Universe 
{
class Body : public SpaceObject, virtual private NonCopyClass 
{
public:

explicit Body(int window_size);

~Body();

void step(double times);


double calNetforce(double radius, double planet1_mass, double planet2_mass);

void updateVelocity(double times);

void set_xVel(double xvel) {
x_vel = xvel;
}

void set_yVel(double yvel) {
y_vel = yvel;
}

double get_xVel() {return x_vel;}

double get_yVel() {return y_vel;}

void set_xPos(double x) {
x_pos = x;
}

void set_yPos(double y) {
y_pos = y;
}

double get_xPos() {return x_pos;}

double get_yPos() {return y_pos;}

void setTimes(double times) {times_ = times;}

double getTimes() {return times_;}

void setMass(float mass) {mass_ = mass;}

double getMass() {return mass_;}

void setBodyTexture(sf::Texture texture) {pTexture_ = texture;}

void createBodyTexture();

void createBodySprite();

void setBodySprite(sf::Sprite sprite) {pSprite_ = sprite;}

sf::Sprite getSprite() {return pSprite_;}

sf::Texture getBodyTexture() {return pTexture_;}

double getNetForce() {return netForce_;}

sf::Vector2f getAcceleration() {return acceleration_;}

sf::Vector2f getPosition() { return pSprite_.getPosition();}

std::string getPlanetName();

void setAcceleration(double x_accel, double y_accel) {
x_accel_ = x_accel;
y_accel_ = y_accel;
acceleration_ = sf::Vector2f(x_accel, y_accel);
}

void setSpritePosition(double x, double y) {
pSprite_.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f getInitScale() {
sf::Vector2f temp = sf::Vector2f(x_pos, y_pos);
return temp;
}

std::string getBodyName() {return planet_name_;}

void draw(sf::RenderTarget& target, sf::RenderStates states) const;


friend std::ostream& operator <<(std::ostream& out_stream,

const Universe::Body& body) {
out_stream << " " << body.x_pos << " ";
out_stream << " " << body.y_pos << " ";
out_stream << " " << body.x_vel << " ";
out_stream << " " << body.y_vel << " ";
out_stream << " " << body.mass_ << " ";
out_stream << " " << body.file_name << " ";
return out_stream;
}



friend std::istream& operator >>(std::istream& in_stream,
Universe::Body& body) {
in_stream >> body.x_pos
>> body.y_pos
>> body.x_vel
>> body.y_vel
>> body.mass_;
std::string image_name;
std::cin >> image_name;
std::cout << body.x_vel << " " << body.y_vel << std::endl;
body.planet_name_ = image_name;
body.parsePlanetName();
body.file_name = "res/" + image_name;
body.pTexture_.loadFromFile(body.file_name);
body.pSprite_.setTexture(body.pTexture_);
return in_stream;
}

void parsePlanetName();
private:
int wSize_; 
double times_; 
sf::Texture pTexture_; 
sf::Sprite pSprite_; 
sf::Vector2f acceleration_; 

double x_pos, y_pos, x_vel, y_vel, mass_;
double x_accel_, y_accel_;
std::string file_name;
std::string planet_name_; 
double netForce_; 

};
} 

#endif