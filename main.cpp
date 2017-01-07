/*********************************************************************
 ** Program Filename: main.cpp
 ** Author: Kyle Cross
 ** Date: 1-3-2017
 ** Description: Contains the main function that runs a maze game where
 ** an ant is tasked with finding honey to save an ant colony.
 *********************************************************************/

#include "gamePlay.hpp"

int main()
{
   srand(static_cast<unsigned int>(time(NULL)));   //Seeds random generator
   
   GamePlay game;                                  //Create instance of game
   
   game.playGame();                                //Play game
      
   return 0;
}


