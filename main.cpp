#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Universe.hpp"
#include "body.hpp"

#define WIN_SIZE 800

int main(int argc, char* argv[]) {
 
  if (argc <= 1) {
    std::cout << "To Execute: ./orbit [Total Times] "
        "[Time per Step] < input" << std::endl;
    return 0;
  }

  
  int number_of_planets;
  std::cin >> number_of_planets;
 
  double universe_radius;
  std::cin >> universe_radius;
  std::vector<Universe::Body*> planetList;

  for (int i = 0; i < number_of_planets; i++) {
    Universe::Body* planet = new Universe::Body(WIN_SIZE);
    std::cin >> *planet;
    std::cout << *planet << std::endl;
    planetList.push_back(planet);
  }

 
  double total_times = static_cast<double>(std::atoi(argv[1]));
  double time_per_step = static_cast<double>(std::atoi(argv[2]));

  
  Universe::Universe universe(universe_radius, WIN_SIZE, planetList);

 
  universe.setTotalTime(total_times);
  universe.setStepTime(time_per_step);

  universe.run();

  return 0;
}
