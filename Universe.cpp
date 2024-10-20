#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>  // For std::stringstream
#include <iomanip>  // For std::setw
#include "Universe.hpp"

const unsigned int numStars = 200;  

// Constructor
Universe::Universe::Universe(double rad, int size, std::vector<std::unique_ptr<Body>>& planetList)
  : winSize_(size), uni_rad(rad), bodyList_(std::move(planetList)), elapsedTime_(0), selectedPlanet_(nullptr) {
  
  if (rad <= 0 || size <= 0) {
    throw std::invalid_argument("Invalid radius: " + std::to_string(rad) + " or size: " + std::to_string(size));
  }

  std::srand(static_cast<unsigned int>(std::time(0)));

  window_.create(sf::VideoMode(winSize_, winSize_), "SOLAR SYSTEM");
  window_.setFramerateLimit(30);
  ship_ = std::make_unique<SpaceShip>(window_.getSize());

  setUpTextAndDialog();
  createStarVertexArray();
}

// Destructor
Universe::Universe::~Universe() {
  // Smart pointers automatically clean up memory
}

// Main simulation loop
void Universe::Universe::run() {
  while (window_.isOpen() && elapsedTime_ < uni_total_times) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      } else if (event.type == sf::Event::KeyPressed) {
        shipMove(event.key);
        
      }
    }

    window_.clear();
    
    checkClickOnSprite();
    updateDialog(selectedPlanet_);
    updateUniverse();

    window_.draw(dialogBox_);
    window_.draw(dialogText_);
    window_.draw(textTime_);
    window_.draw(starVertices_);  // Draw all stars at once
    window_.draw(*ship_);
    window_.display();

    updateTime(static_cast<int>(step_time));
  }
  printState();
}

void Universe::Universe::updateUniverse() {
  for (auto& first_body : bodyList_) {
    double m1 = first_body->getMass();
    double x_force = 0, y_force = 0;

    for (auto& second_body : bodyList_) {
      if (first_body != second_body) {
        sf::Vector2f first_pos = first_body->getInitScale();
        sf::Vector2f second_pos = second_body->getInitScale();

        double m2 = second_body->getMass();
        double x_dif = second_pos.x - first_pos.x;
        double y_dif = second_pos.y - first_pos.y;
        double distance = std::sqrt((x_dif * x_dif) + (y_dif * y_dif));

        if (distance != 0) {  // Prevent division by zero
          double netforce = first_body->calNetforce(distance, m1, m2);
          x_force += netforce * (x_dif / distance);
          y_force += netforce * (y_dif / distance);
        }
      }
    }

    double x_accel = x_force / m1;
    double y_accel = y_force / m1;

    first_body->setAcceleration(x_accel, y_accel);
    first_body->updateVelocity(step_time);
    first_body->step(step_time);

    transformBodies(*first_body);
    window_.draw(*first_body);
  }
}

void Universe::Universe::createStarVertexArray() {
  // Initialize the vertex array to hold all the stars
  starVertices_.setPrimitiveType(sf::Points);
  starVertices_.resize(numStars);

  for (unsigned int i = 0; i < numStars; ++i) {
    sf::Vertex& vertex = starVertices_[i];
    vertex.position = sf::Vector2f(static_cast<float>(std::rand() % winSize_), static_cast<float>(std::rand() % winSize_));
    vertex.color = sf::Color::White;
  }
}

void Universe::Universe::setStepTime(double time_) {
  if (time_ > uni_total_times || time_ <= 0) {
    throw std::runtime_error("Invalid Time per Step: " + std::to_string(time_));
  }
  step_time = time_;
}

void Universe::Universe::setTotalTime(int time_) {
  if (time_ < step_time) {
    throw std::runtime_error("Invalid Total Time: Must be greater than time per step.");
  }
  uni_total_times = time_;
}

void Universe::Universe::transformBodies(Body& body) {
    double x_org = winSize_ / 2.0;
    double y_org = winSize_ / 2.0;

    // Calculate the scaling factor to map universe units to pixels
    double scale = (double)winSize_ / (2.0 * uni_rad);  // Pixels per unit distance

    sf::Vector2f initial = body.getInitScale();  // Universe coordinates

    // Map universe coordinates to screen coordinates
    double x_pos = initial.x * scale + x_org;
    double y_pos = initial.y * scale + y_org;

    body.setSpritePosition(x_pos, y_pos);
}



void Universe::Universe::checkClickOnSprite() {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2i click_coordinates = sf::Mouse::getPosition(window_);

    for (const auto& body : bodyList_) {
      if (body->getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(click_coordinates))) {
        selectedPlanet_ = body.get();
        break;  // Exit loop after selecting one planet
      }
    }
  }
}

void Universe::Universe::setUpTextAndDialog() {
    // Reduce the size of the dialog box
    sf::Vector2f dialog_size(300.f, 100.f);  // Make the dialog box smaller
    sf::Vector2f dialog_pos(window_.getSize().x - dialog_size.x - 10.f, 
                            window_.getSize().y - dialog_size.y - 10.f);  // Reposition it with a margin

    dialogBox_.setSize(dialog_size);  // Set the new size
    dialogBox_.setPosition(dialog_pos);  // Set the new position
    dialogBox_.setFillColor(sf::Color(255, 255, 255, 150));  // Keep the same transparency

    // Set up the text
    if (!fontTime_.loadFromFile("res/fonts.otf")) {
        throw std::runtime_error("Failed to load font");
    }

    textTime_.setFont(fontTime_);
    textTime_.setString("0");
    textTime_.setCharacterSize(14);  // Make the text size smaller if necessary
    textTime_.setFillColor(sf::Color::Black);
    textTime_.setPosition(dialog_pos.x + 10.f, dialog_pos.y + 10.f);  // Position inside the dialog box

    dialogText_.setFont(fontTime_);
    dialogText_.setCharacterSize(12);  // Adjust text size if needed
    dialogText_.setString("Click on a body");  // Default text
    dialogText_.setFillColor(sf::Color::Black);
    dialogText_.setPosition(dialog_pos.x + 10.f, dialog_pos.y + 40.f);  // Adjust text position inside the dialog box
}


void Universe::Universe::updateDialog(Body* planet) {
  if (planet) {
    sf::Vector2f acce = planet->getAcceleration();
    std::stringstream ss;
    std::string name = planet->getPlanetName();
    ss << std::setw(18) << "Planet: " << name << "\n";
    ss << std::setw(18) << "Position: (" << planet->getPosition().x << ", " << planet->getPosition().y << ")\n";
    ss << std::setw(17) << "Velocity: (" << planet->get_xVel() << ", " << planet->get_yVel() << ")\n";
    ss << "Acceleration: (" << acce.x << ", " << acce.y << ")\n";
    dialogText_.setString(ss.str());
  }
}

void Universe::Universe::shipMove(sf::Event::KeyEvent key) {
  //ship_->move(key.code);
  ship_->move(key.code, window_.getSize());
}

void Universe::Universe::updateTime(int time) {
  elapsedTime_ += time;
  setTextTime();
}

void Universe::Universe::setTextTime() {
  textTime_.setString(std::to_string(getElapsedTime()));
}

int Universe::Universe::getElapsedTime() const {
  return elapsedTime_;
}

void Universe::Universe::printState() {
  std::cout << "++++++++++++++ Universe State ++++++++++++++" << std::endl;
  for (const auto& body : bodyList_) {
    std::cout << "Planet: " << body->getPlanetName() << std::endl;
    std::cout << *body << std::endl;
  }
}
