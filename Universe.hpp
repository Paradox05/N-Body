#ifndef UNIVERSE_HPP_
#define UNIVERSE_HPP_
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
#include"SpaceObject.hpp"
#include"Spaceship.hpp"
#include"body.hpp"
#include"star.hpp"
#include <ctime>

namespace Universe 
{
class Universe 
{
public:

Universe(double rad, int size, std::vector<Body*>& planetList);

~Universe();

void run();

sf::Vector2f translateCoordinates(float x, float y);

void printState();

void setTextTime();

int getElapsedTime() const;

void setTotalTime(int time_);

void setStepTime(double time_);

double getStepTime() {return step_time;}

double getTotalTime() {return uni_total_times;}

void transformBodies(Body&);
private:

void fetchBody();

void fetchStar();

void drawStars();

void drawBodies();

void updateTime(int time);

void updateUniverse();

void checkClickOnSprite();
void setUpTextAndDialog();

void updateDialog(Body* planet);

void shipMove(sf::Event::KeyEvent key);
int winSize_; 
int uni_total_times; 
double step_time;
double uni_rad; 
sf::RenderWindow window_;
std::vector<Body*> bodyList_; 
std::vector<Star> starList_; 
SpaceShip* ship_; 
int elapsedTime_;
sf::Font fontTime_; 
sf::Text textTime_; 
sf::RectangleShape dialogBox_;
sf::Text dialogText_; 
Body* selectedPlanet_;
};
} 
#endif 