/*********************************************************************
 ** Program Filename: Player.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: A player class is defined. A player starts with a
 ** set value of turns, pollen grains, and a size of items they can hold.
 ** Items are held in a vector called the backpack. Items in backpack can 
 ** be added, removed, displayed, and searched. Pollen and turns values
 ** are determined.
 ** Input: Name of items.
 ** Output: Values of pollen and turns left. Boolean values relating to 
 ** backpack contents.
 *********************************************************************/

#include "Player.hpp"

Player::Player()
{
   turn = 20;
   pollen = 10;
   backpackSize = 0;
   backpackFull = 8;
}

/*********************************************************************
 ** Function: void addItem(string)
 ** Description: Adds item to backpack vector.
 *********************************************************************/

void Player::addItem(string itemIn)
{
   //Does nothing if backpack is full
   if (backpackSize == backpackFull)
   {
      cout << "Backpack full.\n";
   }
   //Adds item
   else if (itemIn != "")
   {
      backpack.push_back(itemIn);
      backpackSize++;
      
      displayBackpack();
   }
   else
   {
      cout << "Nothing picked up.\n";
   }
}

/*********************************************************************
 ** Function: void removeItem(string)
 ** Description: Searches for item and removes it.
 *********************************************************************/

void Player::removeItem(string itemIn)
{
   if (backpackSize != 0)
   {
      //Searches and removes one item
      for (int i = 0; i < (static_cast<int>(backpack.size())); i++)
      {
         if (backpack[i] == itemIn)
         {
            backpack.erase(backpack.begin()+i);
            backpackSize--;
            break;
         }
      }
   }
}

/*********************************************************************
 ** Function: bool searchItem(string)
 ** Description: Searches for item and returns if found.
 *********************************************************************/

bool Player::searchItem(string itemIn)
{
   //Doesn't search if empty
   if (backpackSize == 0)
   {
      return false;
   }
   //Searches for item
   else
   {
      for (int i = 0; i < (static_cast<int>(backpack.size())); i++)
      {
         if (backpack[i] == itemIn)
         {
            return true;
         }
      }
   }
   return false;
}

/*********************************************************************
 ** Function: void displayBackpack()
 ** Description: Displays all items in backpack.
 *********************************************************************/

void Player::displayBackpack()
{
   //Displays if not empty
   if (backpackSize == 0)
   {
      cout << "Backpack is empty.\n";
   }
   else
   {
      cout << "\nBackpack items:\n";
      
      for (int i = 0; i < (static_cast<int>(backpack.size())); i++)
      {
         cout << backpack[i] << endl;
      }
   }
}


/*********************************************************************
 ** Function: void decrementPollen()
 ** Description: Decrements pollen value.
 *********************************************************************/

void Player::decrementPollen()
{
   if (pollen > 0)
      pollen--;
}

int Player::getPollen()
{
   return pollen;
}

/*********************************************************************
 ** Function: void decrementTurn()
 ** Description: Decrements turn value.
 *********************************************************************/

void Player::decrementTurn()
{
   if (turn >0)
      turn --;
}

int Player::getTurn()
{
   return turn;
}




