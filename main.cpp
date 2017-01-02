/*********************************************************************
 ** Program Filename: main.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Contains the main function that runs a maze game where
 ** an ant is tasked with finding honey to save an ant colony.
 ** Input: User chooses between a menu of options. Inputs direction of moves.
 ** Output: The state of the game is displayed.
 *********************************************************************/


#include "gamePlay.hpp"



/*********************************************************************
 ** Function: int main()
 ** Description: A user chooses from a menu of options what the course
 ** of action is in the game. The user has the ability to move throughout
 ** a linked structure and alter the structure until the goal is reached.
 ** Pre-Conditions: A Space class is defined with the appropriate
 ** derived character classes. A Beehive class contains a linked structure of
 ** spaces and various functions of of the player.
 *********************************************************************/

int main()
{
   srand(static_cast<unsigned int>(time(NULL)));   //Seeds random generator
   
   GamePlay game;
   
   game.playGame();
      
   return 0;
}


