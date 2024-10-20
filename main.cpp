#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>  // For smart pointers
#include "Universe.hpp"
#include "body.hpp"

#define WIN_SIZE 800

int main(int argc, char* argv[]) {
    // Check if enough arguments are provided
    if (argc <= 2) {
        std::cout << "To Execute: ./orbit [Total Times] [Time per Step] < input" << std::endl;
        return 0;
    }

    // Convert command-line arguments to doubles
    try {
        double total_times = std::stod(argv[1]);
        double time_per_step = std::stod(argv[2]);

        // Read the number of planets and universe radius from input
        int number_of_planets;
        std::cin >> number_of_planets;
        
        double universe_radius;
        std::cin >> universe_radius;

        // Use a vector of smart pointers for planets
        std::vector<std::unique_ptr<Universe::Body>> planetList;

        // Read planet data from input
        for (int i = 0; i < number_of_planets; ++i) {
            auto planet = std::make_unique<Universe::Body>(WIN_SIZE);
            std::cin >> *planet;  // Read planet data
            std::cout << *planet << std::endl;  // Print planet data
            planetList.push_back(std::move(planet));
        }

        // Create the Universe object
        Universe::Universe universe(universe_radius, WIN_SIZE, planetList);

        // Set the total time and step time
        universe.setTotalTime(total_times);
        universe.setStepTime(time_per_step);

        // Run the simulation
        universe.run();

    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
