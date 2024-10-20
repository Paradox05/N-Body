#ifndef STAR_HPP_
#define STAR_HPP_
#include<SFML/Graphics.hpp>
#include<algorithm>
#include<vector>
#include"SpaceObject.hpp"

namespace Universe 
{

class Star : public SpaceObject 
{
public:

Star(sf::Vector2u winDimesion, std::vector<Star>& starList);

explicit Star(sf::Vector2f location, double mass = 0.0);

~Star();

private:

virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

sf::Vector2f positionGenerator(sf::Vector2u range,
std::vector<Star>& starList);

float radiusGenerator();
sf::CircleShape shape_;

float
radius_; 
};


}
#endif 
