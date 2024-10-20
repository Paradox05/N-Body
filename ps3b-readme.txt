/**********************************************************************
 *  N-Body Simulation ps3b-readme.txt template
 **********************************************************************/

Name: Roniel Abreu
OS: Linux
Text editor: Visual Studio COde
Hours to complete assignment: more than 7 hours 

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
	The assignment is to create a simulation of a universe by simulating the motion of particles, and animate those results using SFML. 

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/

Using vectors was essential to keep track of positioning and updating the planets in the universe.



/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
When implementing the method named run i implemented a way to move the ship each time a key is pressed here is the code:
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

the condition for the while loop is basically getting an update each time something new happens to the window and withing that statemetnts we have a switch stament which check whether or not we press a key we use one of the functions that the sfml library has which is sf::Event::KeyPressed any time a key is pressed we move the ship in the direction that the key was in. 


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
No help received. 

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
No serious problems encountered.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
