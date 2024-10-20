#include <vector>
#include <string>
#include "Universe.hpp"

const unsigned int numStars = 200;  
const unsigned int numBodies = 6;

Universe::Universe::Universe(double rad, int size,
                             std::vector<Body*>& planetList)
  :winSize_(size), uni_rad(rad) {
  if (rad <= 0 || size <= 0) {
    throw std::invalid_argument("Invalid Parameter(s)");
    return;
  }
  
  std::srand(time(0));

 
  window_.create(sf::VideoMode(winSize_, winSize_),
                 "SOLAR SYSTEM");
  window_.setFramerateLimit(30);
  ship_ = new SpaceShip(window_.getSize());
  setUpTextAndDialog();
  elapsedTime_ = 0;

  

  fetchStar();
  bodyList_ = planetList;
  selectedPlanet_ = NULL;
}

Universe::Universe::~Universe() {
}


void Universe::Universe::run() {
  while (window_.isOpen() && elapsedTime_ < uni_total_times) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window_.close();
          break;
        case sf::Event::KeyPressed:
          shipMove(event.key);
          break;
        default:
          break;
      }
    }
    window_.clear();
    
    checkClickOnSprite();
    updateDialog(selectedPlanet_);
    updateUniverse();
    window_.draw(dialogBox_);
    window_.draw(dialogText_);
    window_.draw(textTime_);
    drawStars();
    window_.draw(*ship_);
    window_.display();

    
    updateTime(step_time);
  }
  printState();
}

void Universe::Universe::updateUniverse() {
  
  std::vector<Body*>::iterator first_it;
  for (first_it = bodyList_.begin(); first_it != bodyList_.end(); ++first_it) {
   
    double m1 = (*first_it)->getMass();

    
    double x_force = 0, y_force = 0;
    double x_accel, y_accel;

    
    std::vector<Body*>::iterator second_it;
    for (second_it = bodyList_.begin(); second_it != bodyList_.end();
         ++second_it) {
      if (*first_it != *second_it) {
        
        sf::Vector2f first_pos = (*first_it)->getInitScale();
        sf::Vector2f second_pos = (*second_it)->getInitScale();

       
        double m2 = (*second_it)->getMass();

        
        double x_dif = second_pos.x - first_pos.x;
        double y_dif = second_pos.y - first_pos.y;
       
        double distance = sqrt((x_dif * x_dif) + (y_dif * y_dif));

        
        double netforce = (*first_it)->calNetforce(distance, m1, m2);

        
        x_force += netforce * (x_dif / distance);
        y_force += netforce * (y_dif / distance);

       
        x_accel = x_force / m1;
        y_accel = y_force / m1;
      }
    }

    
    (*first_it)->setAcceleration(x_accel, y_accel);
    
    (*first_it)->updateVelocity(step_time);
    
    (*first_it)->step(step_time);

    transformBodies(*(*first_it));
    window_.draw(*(*first_it));
  }
}

void Universe::Universe::fetchStar() {
  
  for (unsigned int i = 0; i < numStars; i++)
    starList_.push_back(Star(window_.getSize(), starList_));
}


void Universe::Universe::drawStars() {
  for (unsigned int i = 0; i < starList_.size(); i++)
    window_.draw(starList_.at(i));  
}


void Universe::Universe::fetchBody() {
  for (unsigned int i = 0; i < numBodies; i++) {
    Body* body = new Body(winSize_);
    bodyList_.push_back(body);
  }
}


void Universe::Universe::setStepTime(double time_) {
  if (time_ > uni_total_times || time_ <= 0) {
    throw std::runtime_error("Invlaid Time per Step!");
    return;
  }
  step_time = time_;
}


void Universe::Universe::setTotalTime(int time_) {
  if (time_ < step_time) {
    throw std::runtime_error(
        "Invalid Total Time! Should be bigger then time per step");
    return;
  }
  uni_total_times = time_;
}


void Universe::Universe::drawBodies() {
  std::vector<Body*>::iterator iter;
  for (iter = bodyList_.begin(); iter != bodyList_.end(); ++iter) {
    window_.draw(*(*iter));
  }
}


void Universe::Universe::transformBodies(Body& body) {
  
  double per_pixel = (uni_rad * 2) / winSize_;

  
  double x_org = winSize_ / 2;
  double y_org = winSize_ / 2;

  sf::Vector2f initial = body.getInitScale();

 
  double x_pos = initial.x / per_pixel;
  double y_pos = initial.y / per_pixel;

  
  x_pos += x_org;
  y_pos += y_org;

 
  body.setSpritePosition(x_pos, y_pos);
}


void Universe::Universe::checkClickOnSprite() {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    std::vector<Body*>::iterator itr;
    sf::Sprite sprite;
    sf::Vector2i click_coordinates = sf::Mouse::getPosition(window_);

    for (itr = bodyList_.begin(); itr != bodyList_.end(); ++itr) {
      sprite = (*itr)->getSprite();
      if (sprite.getGlobalBounds()
          .contains(sf::Vector2f(click_coordinates.x, click_coordinates.y))) {
        selectedPlanet_ = *itr;
      }
    }
  }
}


void Universe::Universe::setUpTextAndDialog() {
  sf::Vector2f dialog_size(600, 150);
  sf::Vector2f dialog_pos(window_.getSize().x-dialog_size.x,
                          window_.getSize().y-dialog_size.y);
  dialogBox_.setSize(dialog_size);
  dialogBox_.setPosition(dialog_pos);
  dialogBox_.setFillColor(sf::Color(255, 255, 255, 150));

  fontTime_.loadFromFile("res/fonts.otf");
  textTime_.setFont(fontTime_);
  textTime_.setString("0");
  dialogText_.setFont(fontTime_);
  dialogText_.setString("Click on a body");
  dialogText_.setColor(sf::Color::Black);
  
  dialogText_.setPosition(dialog_pos.x+10, dialog_pos.y);
}


void Universe::Universe::updateDialog(Body *planet) {
  if (planet) {
    sf::Vector2f acce = planet->getAcceleration();
    std::stringstream ss;
    std::string name;
    name = planet->getPlanetName();
    ss << std::setw(18) << "Planet: " << name << std::endl;
    ss << std::setw(18) << "Position: (" << planet->getPosition().x;
    ss << ", " << planet->getPosition().y << ")" << std::endl;
    ss << std::setw(17) << "Velocity: (" << planet->get_xVel();
    ss << ", " << planet->get_yVel() << ")" << std::endl;
    ss << "Acceleration: (" << acce.x << ", " << acce.y << ")" << std::endl;
    std::string message = ss.str();
    dialogText_.setString(message);
  }
}


void Universe::Universe::shipMove(sf::Event::KeyEvent key) {
  ship_->move(key.code);
}

void Universe::Universe::updateTime(int time) {
  elapsedTime_ += time;
  this->setTextTime();
}

void Universe::Universe::setTextTime() {
  std::stringstream ss;
  ss << getElapsedTime();
  textTime_.setString(ss.str());
}

int Universe::Universe::getElapsedTime() const {
  return elapsedTime_;
}

void Universe::Universe::printState() {
  std::vector<Body*>::iterator itr;
  std::cout << "++++++++++++++ Universe State ++++++++++++++" << std::endl;
  for (itr = bodyList_.begin(); itr != bodyList_.end(); ++itr) {
    std::cout << "Planet: " << (*itr)->getPlanetName() << std::endl;
    std::cout << *(*itr) << std::endl;
  }
}