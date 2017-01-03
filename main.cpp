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

int main()
{
   srand(static_cast<unsigned int>(time(NULL)));   //Seeds random generator
   
   GamePlay game;
   
   game.playGame();
      
   return 0;
}


