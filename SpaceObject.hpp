#ifndef SPACEOBJECT_HPP_
#define SPACEOBJECT_HPP_

#include <SFML/Graphics.hpp>

namespace Universe {

class SpaceObject : public sf::Drawable {
public:
    virtual ~SpaceObject();  // Ensure virtual destructor for polymorphic behavior

    const sf::Vector2f& getLocation() const;
    void setLocation(const sf::Vector2f& location);

    const sf::Vector2u& getVelocity() const;
    void setVelocity(const sf::Vector2u& velocity);

    virtual double getMass() const;  // Make this virtual to allow overriding
    void setMass(double mass);

protected:
    SpaceObject();
    SpaceObject(sf::Vector2f location, sf::Vector2u velocity, double mass);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    sf::Vector2f position_;
    sf::Vector2u velocity_;
    double mass_;
};

}  // namespace Universe

#endif  // SPACEOBJECT_HPP_
