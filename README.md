# N-Body Simulation

## Overview
This project is an **N-Body Simulation** that simulates the motion of celestial bodies (such as planets) under the influence of gravitational forces. The simulation is based on the laws of Newtonian physics, and it uses **SFML (Simple and Fast Multimedia Library)** for rendering the visual representation of the solar system.

You can observe the interactions between planets, a black hole, and other objects as they move and affect each other through gravity.

## Features
- Simulates the gravitational interactions between multiple celestial bodies.
- Includes planets, the sun, and a black hole as objects.
- Uses SFML to visualize the objects in a 2D window.
- Adjustable simulation parameters like total time and time steps.
## Explanation

### What is an N-Body Simulation?
An N-Body simulation models the motion and gravitational interaction between multiple bodies (such as planets, stars, and black holes) in space. The simulation computes the forces acting on each body due to all other bodies, then updates their positions and velocities over time based on these forces.

This project simulates a small solar system, with the sun at the center and several planets (and a black hole) orbiting around it. It calculates gravitational forces using Newton's law of universal gravitation.

### How It Works
1. **Input**: 
   - The simulation takes an input file that describes the initial conditions of the celestial bodies. This includes their starting positions, velocities, masses, and image assets.
   - The first line of the input file specifies the number of celestial bodies and the radius of the universe.
   
2. **Physics Engine**:
   - The forces between every pair of bodies are calculated using the formula:
     \[
     F = \frac{G \cdot m_1 \cdot m_2}{r^2}
     \]
     Where:
     - \( G \) is the gravitational constant.
     - \( m_1 \) and \( m_2 \) are the masses of the two bodies.
     - \( r \) is the distance between the two bodies.
   - These forces are used to calculate each body's acceleration, velocity, and updated position over small time steps.

3. **Rendering**:
   - The simulation uses **SFML (Simple and Fast Multimedia Library)** to render the celestial bodies. Each body is represented by an image (such as `earth.gif` or `sun.gif`) which is displayed in a window.
   - The positions of the bodies are updated in each frame of the simulation, and SFML draws them on the screen according to their new positions.

4. **Time Steps**:
   - The simulation runs over a specified total time, divided into small increments called time steps. In each time step, the positions and velocities of all bodies are updated according to the forces they experience.

5. **Black Hole**:
   - A special object in the simulation, the black hole, has an extremely large mass and exerts a significant gravitational force on other celestial bodies, causing them to be pulled toward it.

### Code Organization
- **main.cpp**: 
  - This is the entry point of the simulation. It reads the input file, sets up the celestial bodies, and starts the simulation loop.
  
- **Universe.cpp/Universe.hpp**:
  - These files manage the entire simulation. They handle the gravitational calculations, updating the bodies' positions and velocities, and rendering them on the screen using SFML.
  - The `Universe` class contains methods like `run()` (the main loop of the simulation), `updateUniverse()` (which updates positions and velocities), and `transformBodies()` (which scales the bodies' universe positions to screen positions).

- **body.cpp/body.hpp**:
  - The `Body` class represents individual celestial bodies (such as planets). It stores their positions, velocities, and masses and provides methods for calculating forces, updating velocities, and rendering the bodies.

- **Spaceship.cpp/Spaceship.hpp** (optional):
  - This is a feature that allows the user to control a spaceship in the simulation. The spaceship can move around the universe but is not affected by gravitational forces.

- **star.cpp/star.hpp**:
  - These files handle rendering background stars in the simulation, using a vertex array for efficient drawing.

- **NonCopyClass.hpp**:
  - A utility class that prevents certain objects from being copied. This is useful for objects like the universe, where making multiple copies would cause unexpected behavior.

### Adjusting the Simulation
- **Window Size**: The window size is set to `1200x1200` pixels, but this can be modified in `Universe.cpp` to fit larger or smaller screens.
- **Scaling**: The positions of celestial bodies are scaled to fit the window size. If planets appear too close or too far apart, you can adjust the universe radius or the scaling factor in the `transformBodies()` method.
- **Input File**: You can change the initial positions, velocities, and masses of celestial bodies by editing the input file. The number of bodies and their properties can also be modified to simulate different scenarios.


## Prerequisites

### Required Software
- **SFML**: The simulation uses the SFML library for graphics rendering. Make sure you have SFML installed. You can install it using Homebrew on macOS:

  ```bash
  brew install sfml
  ```
 - C++ Compiler: Ensure you have a C++17 compatible compiler (like g++) installed.

## Installation
1.) Clone the Repository:
  ```bash
  git clone https://github.com/your-username/n-body-simulation.git
  cd n-body-simulation
  ```
2.) Compile the Project: Use the provided Makefile to compile the project:
  ```bash
  make
  ```
## Usage
To run the simulation, use the following command:
```bash
./orbit_simulation [Total Time] [Time Per Step] < input_file.txt
```
- [Total Time]: The total time for which the simulation will run.
- [Time Per Step]: The time step for each iteration of the simulation.
- input_file.txt: The input file containing the initial positions, velocities, and masses of the celestial bodies.

## Example
```bash
./orbit_simulation 10000 250 < input_file.txt
```
## Input File Format
The input file should have the following format:
```css
[number of bodies]
[universe radius]
[x_pos] [y_pos] [x_vel] [y_vel] [mass] [image_file]
...
```
For example: 
```python
11
3.00e+12
1.4960e+11   1.0000e+11    0.0000e+00   2.9800e+04   5.9740e+24   earth.gif
2.2790e+11  -1.5000e+11    0.0000e+00   2.4100e+04   6.4190e+23   mars.gif
...
8.0000e+11   0.0000e+00    0.0000e+00   1.0000e+31   1.0000e+40   blackhole.gif
```
## Output
The simulation will display a window showing the motion of celestial bodies over time, according to the gravitational forces between them.

## Configuration
### Window Size

The window size is set to 1200x1200 pixels. You can modify this in the Universe.cpp file if you need a larger or smaller window.

### Scaling and Adjustments
If planets appear too close or too far from each other, you can adjust the universe radius in the input file, or modify the scaling factor in the Universe::transformBodies() function.


## File Structure
```bash
.
├── body.cpp              # Implementation of the Body class (celestial objects like planets)
├── body.hpp              # Header file for the Body class
├── main.cpp              # Entry point for running the N-Body simulation
├── Makefile              # Build instructions for compiling the project
├── Spaceship.cpp         # Implementation of the SpaceShip class (optional spaceship feature)
├── Spaceship.hpp         # Header file for the SpaceShip class
├── star.cpp              # Implementation of the Star class (for rendering stars) NOT USED
├── star.hpp              # Header file for the Star class NOT USED
├── Universe.cpp          # Handles the simulation of the universe and gravitational interactions
├── Universe.hpp          # Header file for the Universe class
├── NonCopyClass.hpp      # Utility class that prevents copying of certain objects
├── res/                  # Folder containing image assets (e.g., planets, blackhole, etc.)
│   ├── earth.gif         # Image of Earth used in the simulation
│   ├── mars.gif          # Image of Mars used in the simulation
│   └── ...               # Other planet images (sun.gif, venus.gif, etc.)
└── README.md             # Project description and usage instructions
```

## Resources

- [SFML Official Documentation](https://www.sfml-dev.org/documentation/2.5.1/): This is the official documentation for SFML, which provides detailed information on using the SFML library for graphics, window handling, audio, and more.
  
- [Newton's Law of Universal Gravitation](https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation): This Wikipedia article explains the physics behind the gravitational interactions that are simulated in this project.
  
- [SFML Setup Guide](https://www.sfml-dev.org/tutorials/2.5/start-linux.php): A guide on how to set up SFML on various platforms (Linux, macOS, Windows), in case you're having trouble getting the library working.


