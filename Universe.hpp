#ifndef UNIVERSE_HPP_
#define UNIVERSE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "SpaceObject.hpp"
#include "Spaceship.hpp"
#include "body.hpp"

namespace Universe {

class Universe {
public:
    // Constructor
    Universe(double rad, int size, std::vector<std::unique_ptr<Body>>& planetList);

    // Destructor
    ~Universe();

    // Main simulation loop
    void run();

    // Update the time text display
    void setTextTime();

    // Get elapsed time
    int getElapsedTime() const;

    // Set total simulation time
    void setTotalTime(int time_);

    // Set step time for simulation
    void setStepTime(double time_);

    // Transform the body coordinates
    void transformBodies(Body&);

private:
    void printState();
    // Initialize the vertex array for stars
    void createStarVertexArray();

    // Update the universe by calculating forces, velocities, and positions
    void updateUniverse();

    // Handle mouse clicks on planet sprites
    void checkClickOnSprite();

    // Set up the text and dialog box
    void setUpTextAndDialog();

    // Update the dialog box with planet information
    void updateDialog(Body* planet);

    // Handle spaceship movement
    void shipMove(sf::Event::KeyEvent key);

    // Update the simulation time
    void updateTime(int time);

    // Window size (square window)
    int winSize_; 

    // Total simulation time
    int uni_total_times;

    // Time step for the simulation
    double step_time;

    // Universe radius
    double uni_rad;

    // SFML window
    sf::RenderWindow window_;

    // List of bodies (planets, etc.)
    std::vector<std::unique_ptr<Body>> bodyList_; 

    // Vertex array for drawing stars efficiently
    sf::VertexArray starVertices_;

    // Spaceship pointer (managed via smart pointer)
    std::unique_ptr<SpaceShip> ship_;

    // Elapsed simulation time
    int elapsedTime_;

    // Font for text display
    sf::Font fontTime_; 

    // Text display for time
    sf::Text textTime_;

    // Rectangle shape for dialog box
    sf::RectangleShape dialogBox_;

    // Text inside the dialog box
    sf::Text dialogText_;

    // Pointer to the selected planet
    Body* selectedPlanet_;
};

}  // namespace Universe

#endif  // UNIVERSE_HPP_
