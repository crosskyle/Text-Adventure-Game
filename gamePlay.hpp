/*********************************************************************
 ** Program Filename: gamePlay.hpp
 ** Author: Kyle Cross
 ** Date: 1-3-2017
 ** Description: Runs a maze game where an ant is tasked with finding honey
 ** to save an ant colony. A json file is used to read the game's text to the
 ** screen. The user has the options to move, pick up items, deposit pollen,
 ** and show picked up items that are in a backpack vector. The user navigates a linked
 ** structure that is manipulated in a 'Beehive' class. The Beehive class contains
 ** different spaces and the player that navigates the spaces in the game world.
 ** Input: User chooses between a menu of options. Inputs direction of moves.
 ** Output: The state of the game is displayed.
 *********************************************************************/

#ifndef gamePlay_hpp
#define gamePlay_hpp

#include "Beehive.hpp"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

class GamePlay
{
private:
   char choice;                  //Holds user's choice from game menu
   char move;                    //Holds direction user would like to move
   Beehive play;                 //Instance of the beehive containing the game world
   std::string parse(std::string stringIn);
   char getMenuOption(char &choice, json j);
   char getDirection(char &move, json j);
   void displayLocation(json j);
   
public:
   void playGame();
};

#endif
