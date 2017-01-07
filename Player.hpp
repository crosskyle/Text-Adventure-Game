/*********************************************************************
 ** Program Filename: Player.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: A player class is declared. A player starts with a
 ** set value of turns, pollen grains, and a size of items they can hold.
 ** Items are held in a vector called the backpack. Items in backpack can
 ** be added, removed, displayed, and searched. Pollen and turns values
 ** are determined.
 ** Input: Name of items.
 ** Output: Values of pollen and turns left. Boolean values relating to
 ** backpack contents.
 *********************************************************************/

#ifndef Player_hpp
#define Player_hpp

#include <vector>
#include <iostream>
#include <string>

class Player
{
private:
   std::vector<std::string> backpack;        //Holds items added
   int backpackFull;                         //Capacity of backpack
   int backpackSize;                         //Position in vector
   int pollen;                               //Holds number of pollen grains left
   int turn;                                 //Holds turns left
   
public:
   Player();
   void addItem(std::string itemIn);
   void removeItem(std::string itemIn);
   bool searchItem(std::string itemIn);
   void displayBackpack();
   void decrementPollen();
   int getPollen();
   void decrementTurn();
   int getTurn();
};

#endif 
